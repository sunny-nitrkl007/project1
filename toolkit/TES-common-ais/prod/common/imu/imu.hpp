#pragma once

#ifndef IMU_IMU_HPP_
#define IMU_IMU_HPP_

#include <cmath>

#include <geometry/primitives/Angle.h>
#include <geometry/primitives/Vector3D.h>
#include <geometry/rotations/RMatrix3D.h>
#include <geometry/rotations/EulerAngles.h>
#include <geometry/conversions/EulerAnglesToRMatrix3D.h>

namespace tes_common_ais {
    namespace imu {
        template <typename V>
        class LowPassFilter {
        public:
            LowPassFilter(float factor) :
                reset_(true),
                factor_(factor),
                output_() {}

            LowPassFilter() : LowPassFilter(1.f) {}

            const V& update(const V& input) {
                if (reset_) {
                    output_ = input;
                    reset_ = false;
                }
                else {
                    output_ = output_ + factor_ * (input - output_);
                }
                return output_;
            }

            const V& output() const { return output_; }

            float factor() const {return factor_; }
            float factor(float value) { return factor_ = value; }

            void reset() { reset_ = true; }

        private:
            bool reset_;
            float factor_;
            V output_;
        };

        template <typename V>
        class DoubleLowPassFilter {
        public:
            DoubleLowPassFilter(float factor) :
                filt1_(factor),
                filt2_(factor) {}

            DoubleLowPassFilter() : DoubleLowPassFilter(1.f) {}

            const V& update(const V& input) {
                return filt2_.update(filt1_.update(input));
            }

            const V& output() const { return filt2_.output(); }

            float factor() const {return filt2_.factor(); }
            float factor(float value) { return filt2_.factor(filt1_.factor(value)); }

            void reset() {
                filt1_.reset();
                filt2_.reset();
            }
        private:
            LowPassFilter<V> filt1_;
            LowPassFilter<V> filt2_;
        };

        template <typename V>
        class NotchFilter {
        public:
            NotchFilter(float updatePeriodSeconds, float cf, float damping=1.f) :
                reset_(true),
                a_(0.f), b_(0.f), g_(0.f),
                in_1_(), in_2_(),
                output_(), out_1_(), out_2_() {

                // Temporary Computations
                float q = cf * updatePeriodSeconds / 2.f;
                q *= q;

                float r = cf * damping * updatePeriodSeconds;
                float p = 1.f + q;
                float s = 2.f * (q - 1.f);
                float t = p + r;

                a_ = p / t;
                b_ =  s / t;
                g_ = r / t;
            }

            const V& update(const V& input) {
                if (reset_) {
                    in_1_ = input;
                    in_2_ = input;
                    output_ = input;
                    out_1_ = input;
                    out_2_ = input;
                    reset_ = false;
                }
                else {
                    out_2_ = out_1_;
                    out_1_ = output_;

                    output_ = a_ * (input + in_2_ - out_2_);
                    output_ += b_ * (in_1_ - out_1_);
                    output_ += g_ * out_2_;

                    in_2_ = in_1_;
                    in_1_ = input;
                }
                return output_;
            }

            const V& output() const { return output_; }

            void reset() { reset_ = true; }

        private:
            bool reset_;
            float a_;
            float b_;
            float g_;
            V in_1_;
            V in_2_;
            V output_;
            V out_1_;
            V out_2_;
        };

        template <typename V>
        class ComplementaryFilter {
        public:
            ComplementaryFilter(float updatePeriodSeconds, float factor) :
                reset_(true),
                T_(updatePeriodSeconds),
                factor_(factor),
                inputPrevious_(),
                inputDotPrevious_(),
                output_(),
                residual_() {}

            ComplementaryFilter(float updatePeriodSeconds) :
                ComplementaryFilter(updatePeriodSeconds, 0.f) {}

            const V& update(const V& input, const V& inputDot) {
                if (reset_) {
                    output_ = input;
                    residual_ = V();
                    reset_ = false;
                }
                else {
                    auto projected = output_ + ((inputDot + inputDotPrevious_) * T_ / 2.f);
                    output_ = input + factor_ * (projected - input);
                    residual_ = inputDot - ((input - inputPrevious_) / T_);
                }
                inputPrevious_ = input;
                inputDotPrevious_ = inputDot;
                return output_;
            }

            const V& output() const { return output_; }
            const V& residual() const { return residual_; }

            float factor() const {return factor_; }
            float factor(float value) { return factor_ = value; }

            float T() const { return T_; }
            float T(float updatePeriodSeconds) { return T_ = updatePeriodSeconds; }

            void reset() { reset_ = true; }

        private:
            bool reset_;
            float T_;
            float factor_;
            V inputPrevious_;
            V inputDotPrevious_;
            V output_;
            V residual_;
        };

        /*
         * IMU: Represents an inertial measurement unit (IMU)
         * - Encapsulates, and gives access to, the orientation calibration matrix.
         * - Does not include the location of the IMU, the origin is the IMU itself.
         * - If a reference velocity is given, it can be used in velocity fusion and centripetal acceleration compensation.
         */
        class IMU {
        public:
            typedef nrec::geometry::Radian<float> Radian;
            typedef nrec::geometry::Angle<float> Angle;
            typedef nrec::geometry::Vector3D<float> Vector;
            typedef nrec::geometry::RMatrix3D<float> RMatrix;
            typedef nrec::geometry::EulerAngles<float, nrec::geometry::EulerAngleOrder::ZYX> EulerAngles;

            struct Config {
                float updatePeriodSeconds; // The update period
                struct {
                    float jerkFilterFactor;
                    float angAccelFilterFactor;
                    float biasFilterFactor; // Low pass filter factor for bias estimation
                    float speedThreshold; // Linear speed threshold to enable bias estimation
                    float jerkThreshold; // Jerk threshold to enable bias estimation
                    float angAccelThreshold; // Angular acceleration threshold to enable bias estimation
                    float angVelThreshold; // Angular velocity threshold to enable bias estimation
                    float debounceTimeSeconds; // Time for conditions to be true before updating bias estimation
                } bias;
                float angFusionFilterFactor;
                float rollFilterFactor;
                float pitchNotchFrequency; // rad/s
                float pitchNotchDamping;
                float pitchFilterFactor;
                float velFusionFilterFactor;
            };

            static const Config& defaultConfig() {
                static const Config config {
                    0.1f, // Update period in seconds
                    { 0.f, }, // Bias config, effectively disabled
                    0.f, // Angle Fusion, use pure accelerometer, no gyro
                    1.f, // Roll Filter, all pass
                    7.5f, // ~1.2 Hz Pitch Notch Filter
                    0.75f, // Pitch Notch Damping Ratio
                    1.f, // Pitch Filter, all pass
                    0.f // Velocity Fusion, use provided reference, no accelerometer
                };
                return config;
            }

            IMU(const Config& config, const RMatrix& calRMatrix) :
                config_(config),
                calRMatrix_(calRMatrix),
                jerkFilter_(config.bias.jerkFilterFactor),
                angAccelFilter_(config.bias.angAccelFilterFactor),
                biasAngVelFilter_(config.bias.biasFilterFactor),
                magJerk_(0.f),
                magAngAccel_(0.f),
                maxAngVel_(0.f),
                biasConditionTimer_(0.f),
                biasAngVel_(0.f),
                rawLinAccel_(-9.80665f * Vector::UnitZAxis),
                rawAngVel_(0.f),
                adjAngVel_(0.f),
                calLinAccel_(-9.80665f * Vector::UnitZAxis),
                calAngVel_(0.f),
                estLinVelPrevious_(0.f),
                estLinVel_(0.f),
                angFusion_(config.updatePeriodSeconds, config.angFusionFilterFactor),
                rollFilter_(config.rollFilterFactor),
                roll_(Angle::AngleZero),
                pitchNotchFilter_(config.updatePeriodSeconds, config.pitchNotchFrequency, config.pitchNotchDamping),
                pitchFilter_(config.pitchFilterFactor),
                pitch_(Angle::AngleZero),
                orientationRMatrix_(RMatrix::Identity),
                gravityVector_(g()),
                velFusion_(config.updatePeriodSeconds, config.velFusionFilterFactor) {}

            IMU() : IMU(defaultConfig(), RMatrix::Identity) {}

            void setConfig(const Config& config) {
                *this = IMU(config, calRMatrix_);
            }

            void setCalRMatrix(const RMatrix& calRMatrix) {
                *this = IMU(config_, calRMatrix);
            }

            void update(const Vector& rawLinAccel, const Vector& rawAngVel, const Vector& refLinVel, bool inhibitBiasEstimation=false) {
                /*
                 * First you have to take care of gyro bias.  There is a deg/s offset that can be significant.
                 *
                 * Remove centripetal acceleration. Using measured angular velocity crossed with previously estimated
                 * linear velocity, we can estimate centripetal acceleration and remove it from the linear acceleration
                 * vector.  Once the orientation is known, the gravity vector can be removed and you are left with
                 * linear acceleration of the machine that is then used for velocity fusion and estimation.
                 *
                 * Remove linear acceleration. The derivative of previously estimated linear velocity can be
                 * removed from the the linear acceleration vector to be left with linear acceleration that
                 * represent only the gravity vector.
                 *
                 * Estimate pitch and roll from centripetal and linear acceleration compensated linear acceleration vector.
                 *
                 * Fuse estimated pitch and roll with the measured angular velocity in order to get a better/faster
                 * estimate of angular position.  This is the best estimate of machine orientation.
                 *
                 * Now that we know pitch and roll orientation, we can remove gravity from the centripetal acceleration
                 * compensated linear acceleration vector.  Now we are left with estimated linear accelerations.
                 *
                 * Fuse estimated linear accelerations with the measured reference velocities (machined speed)
                 * in order to get a better/faster estimate of linear velocities.  This is the best estimate of
                 * linear velocities.
                 *
                 * Use the estimated linear velocities in the next update.
                 */
                rawLinAccel_ = rawLinAccel;
                rawAngVel_ = rawAngVel;

                // Handle angular velocity bias
                // Allow externally provided bias estimation inhibit signal (like machine idle status)
                {
                    // Estimate instantaneous jerk.
                    Vector jerk = (rawLinAccel - jerkFilter_.update(rawLinAccel)) / config_.updatePeriodSeconds;
                    magJerk_ = nrec::geometry::lengthL2<float>(jerk);

                    // Estimate instantaneous angular acceleration.
                    Vector angAccel = (rawAngVel - angAccelFilter_.update(rawAngVel)) / config_.updatePeriodSeconds;
                    magAngAccel_ = nrec::geometry::lengthL2<float>(angAccel);

                    // Calculate linear speed in m/s.
                    float speed = nrec::geometry::lengthL2<float>(refLinVel);

                    // Take the maximum angular velocity along any axis.
                    maxAngVel_ = nrec::geometry::lengthLInfinity<float>(rawAngVel);

                    if ((speed <= config_.bias.speedThreshold) &&
                            (magJerk_ <= config_.bias.jerkThreshold) &&
                            (magAngAccel_ <= config_.bias.angAccelThreshold) &&
                            (maxAngVel_ <= config_.bias.angVelThreshold) &&
                            (!inhibitBiasEstimation)) {
                        if (biasConditionTimer_ < config_.bias.debounceTimeSeconds) {
                            biasConditionTimer_ += config_.updatePeriodSeconds;
                        }
                        else {
                            // Conditions are met to update the bias estimate.
                            biasAngVel_ = biasAngVelFilter_.update(rawAngVel);
                        }
                    }
                    else {
                        biasConditionTimer_ = 0.f;
                    }
                }

                // Apply the bias adjustment
                Vector adjAngVel = rawAngVel - biasAngVel_;
                adjAngVel_ = adjAngVel;

                // Apply the calibration rotations to raw linear acceleration and angular velocity
                Vector calLinAccel = calRMatrix_ * rawLinAccel;
                calLinAccel_ = calLinAccel;

                Vector calAngVel = calRMatrix_ * adjAngVel;
                calAngVel_ = calAngVel;

                // Remove centripetal acceleration
                Vector centripetalAccel = nrec::geometry::cross(calAngVel, estLinVel_);
                Vector noCentripLinAccel = calLinAccel - centripetalAccel;

                // Take the unfiltered derivative of estimated linear velocity
                Vector estLinAccel = (estLinVel_ - estLinVelPrevious_) / config_.updatePeriodSeconds;

                // After removing both centripetal and linear acceleration, we should be left with acceleration due to gravity.
                Vector rawGravityVector = noCentripLinAccel - estLinAccel;

                // Calculate angular position, pitch and roll.
                // This is unfiltered at this point.
                Vector angPosition;

                {
                    float x, y, z;

                    // Make sure the raw gravity vector magnitude is not crazy.
                    if (nrec::geometry::lengthL2<float>(rawGravityVector) > G()/10.f) {
                        x = rawGravityVector.x();
                        y = rawGravityVector.y();
                        z = rawGravityVector.z();
                    }
                    else {
                        // The raw orientation matrix magnitude is crazy (are we on earth?)
                        // It could be because estimated linear velocity is crazy.
                        // It could be because the IMU is crazy.
                        // Dead reckon from the previous orientation
                        x = gravityVector_.x();
                        y = gravityVector_.y();
                        z = gravityVector_.z();
                    }

                    angPosition.x() = std::atan2(-y, -z);
                    angPosition.y() = std::atan2(x, std::sqrt(y*y+z*z));
                }

                // Do angle fusion here... include integrated angular velocity and angular position
                {
                    /*
                     * These are in the machine frame
                     * - If were were driving along a totally flat turn, clock-wise
                     *   yaw rate would be positive and all other rotations zero.
                     * - If we were driving along a 90 degree banked turn, hotwheels style,
                     *   pitch rate would be the only positive component.
                     *   The machine position would be rolled by 90 degrees positive X.
                     * - If we were driving along a 45 degree banked turn, pitch rate and yaw rate
                     *   would be positive, but are we actually increasing pitch?
                     */

                    // Double invert the rotation matrix, rotate the frame in the opposite direction
                    // of the body orientation.  Invert once for 'opposite direction', invert again
                    // for passive rotation (change of basis)
                    Vector angVel = orientationRMatrix_ * calAngVel;

                    // Update the complementary filters
                    angPosition = angFusion_.update(angPosition, angVel);
                }

                Angle roll(Radian(angPosition.x()));
                Angle pitch(Radian(angPosition.y()));

                // Now that we have the final estimate of position, calculate the rotation matrix
                // that got the IMU to this position.
                {
                    EulerAngles angles(Angle::AngleZero, pitch, roll);
                    nrec::geometry::convertEulerAnglesToRMatrix3D(angles, orientationRMatrix_);
                }

                // Use the newly estimated orientation get the gravity vector in the body frame
                {
                    // Rotate g by the inverse of the orientation because this is a passive rotation, change of basis.
                    RMatrix R = nrec::geometry::getInverse(orientationRMatrix_);
                    gravityVector_ = R * g();
                }

                // Remove the gravity vector to get the estimated linear acceleration
                estLinAccel = noCentripLinAccel - gravityVector_;

                // Estimate linear velocity
                // Subclass could be used to include known kinematics of the machine?
                // - For the chassis IMU, we could know machine speed
                // - For the lift arm IMU we could know machine speed and point of rotation (A-pin) location.
                estLinVelPrevious_ = estLinVel_;
                estLinVel_ = velFusion_.update(refLinVel, estLinAccel);

                // Filter the pitch and roll
                roll_ = rollFilter_.update(roll);
                pitch_ = pitchFilter_.update(pitchNotchFilter_.update(pitch));
            }

            void update(const Vector& rawLinAccel, const Vector& rawAngVel) {
                update(rawLinAccel, rawAngVel, Vector::NullVector, false);
            }

            void update(const Vector& rawLinAccel) {
                update(rawLinAccel, Vector::NullVector, Vector::NullVector, false);
            }

            // Some inputs are unknown, reset state based processing
            void reset() {
                jerkFilter_.reset();
                angAccelFilter_.reset();
                magJerk_ = 0.f;
                magAngAccel_ = 0.f;
                maxAngVel_ = 0.f;
                biasConditionTimer_ = 0.f;

                estLinVelPrevious_ = Vector::NullVector;
                estLinVel_ = Vector::NullVector;

                angFusion_.reset();

                rollFilter_.reset();
                roll_ = Angle::AngleZero;

                pitchNotchFilter_.reset();
                pitchFilter_.reset();
                pitch_ = Angle::AngleZero;

                orientationRMatrix_ = RMatrix::Identity;
                gravityVector_ = g();

                velFusion_.reset();
            }

            Angle roll() const { return roll_; }
            float rollRadians() const { return roll_.getRadians(); }
            float rollDegrees() const { return roll_.getDegrees(); }
            float rollGrade() const { return 100.f * roll_.tan(); }

            Angle pitch() const { return pitch_; }
            float pitchRadians() const { return pitch_.getRadians(); }
            float pitchDegrees() const { return pitch_.getDegrees(); }
            float pitchGrade() const { return 100.f * pitch_.tan(); }

            // This is side-slope about the earth frame X axis.
            Angle vehicleRoll() const { return Angle(Radian(vehicleRollRadians())); }
            float vehicleRollRadians() const { return std::asin(roll_.sin() * pitch_.cos()); }
            float vehicleRollDegrees() const { return vehicleRoll().getDegrees(); }
            float vehicleRollGrade() const {
                float t = roll_.sin() * pitch_.cos();
                return 100.f * t / std::sqrt(1 - t*t);
            }

            // The angular velocity bias in the IMU frame
            Vector biasAngVelVector() const { return biasAngVel_; }

            // This is not filtered by the pitch and roll filters.
            RMatrix orientationRMatrix() const { return orientationRMatrix_; }
            Vector gravityVector() const { return gravityVector_; }

            Vector calibratedLinAccelVector() const { return calLinAccel_; }
            Vector estimatedLinVelVector() const { return estLinVel_; }

            Vector calibratedAngVelVector() const { return calAngVel_; }

            static constexpr float G() { return 9.80665f; }

            static const Vector& g() {
                // The gravity vector in the earth frame.
                // We are in a Z-DOWN coordinate system and the gravity vector points up, so it is negative.
                static const Vector g = -G() * Vector::UnitZAxis;
                return g;
            }


            Config config_;
            RMatrix calRMatrix_; // From IMU frame to body frame

            DoubleLowPassFilter<Vector> jerkFilter_;
            DoubleLowPassFilter<Vector> angAccelFilter_;
            DoubleLowPassFilter<Vector> biasAngVelFilter_;
            float magJerk_;
            float magAngAccel_;
            float maxAngVel_;
            float biasConditionTimer_;
            Vector biasAngVel_; // In the original IMU frame

            Vector rawLinAccel_; // In the original IMU frame
            Vector rawAngVel_; // In the original IMU frame

            Vector adjAngVel_; // In the original IMU frame - bias adjusted

            Vector calLinAccel_; // In the body frame
            Vector calAngVel_; // In the body frame

            Vector estLinVelPrevious_; // In the body frame
            Vector estLinVel_; // In the body frame

            ComplementaryFilter<Vector> angFusion_;

            DoubleLowPassFilter<Angle> rollFilter_;
            Angle roll_; // Around body frame X

            NotchFilter<Angle> pitchNotchFilter_;
            DoubleLowPassFilter<Angle> pitchFilter_;
            Angle pitch_; // Around intermediate frame (base frame since yaw is 0) Y

            RMatrix orientationRMatrix_; // Orientation of body in earth frame, active rotation
            Vector gravityVector_; // The gravity vector in the body frame

            ComplementaryFilter<Vector> velFusion_;

        protected:
        private:
        };
    }
}

#endif // IMU_IMU_HPP_
