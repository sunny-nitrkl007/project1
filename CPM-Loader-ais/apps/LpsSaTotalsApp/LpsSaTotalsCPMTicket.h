#pragma once

#ifndef LPSSATOTALSCPMTICKET_HPP
#define LPSSATOTALSCPMTICKET_HPP

#include <vector>
#include <array>
#include <chrono>

#include <chrono/print.hpp>
#include <chrono/convert.hpp>

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>
#include "CPMTicket/CPMTicket.pb.h"

namespace CPMTicket {

    
    inline void generateCPMTicket(std::ofstream &os, const LpsSaLoadRecordChannelStorage& loadRecord) {
        
        namespace cpmticket = cat::cpm::ticket;
        cpmticket::Ticket Ticket;
        
        // Set trigger
        auto storeAction = loadRecord.storeAction();
        if (storeAction == LpsSaLoadRecordStoreAction::AUTO) {
            Ticket.set_trigger(cpmticket::Ticket_TRIGGER_AUTO);
        }
        else if (storeAction == LpsSaLoadRecordStoreAction::TICKET_LEGAL_FOR_TRADE)
        {
            Ticket.set_trigger(cpmticket::Ticket_TRIGGER_TICKET_LEGAL_FOR_TRADE);
        }
        else if (storeAction == LpsSaLoadRecordStoreAction::TICKET_NOT_FOR_TRADE)
        {
            Ticket.set_trigger(cpmticket::Ticket_TRIGGER_TICKET_NOT_FOR_TRADE);
        }
        else {
            Ticket.set_trigger(cpmticket::Ticket_TRIGGER_TICKET_NOT_FOR_TRADE);
        }

        // Set time and shm that this ticket began. We will start with the first subtotal
        //   start time and shm but replace with the oldest if there is one
        auto timeUtc = loadRecord.getSubtotalByIndex(1).startTime.utcTime;
        int16_t localTimeOffset = tes_common_ais::getLocalTimeOffset(timeUtc).count();
        auto shmTimeTicketStart = loadRecord.getSubtotalByIndex(1).startTime.shmTime;
        auto secsTicketStart =  std::chrono::duration_cast<std::chrono::seconds>(timeUtc.time_since_epoch()).count();
        int16_t localTimeOffsetTicketStart = localTimeOffset;

        // Set ticket id
        Ticket.set_ticket_id(loadRecord.ticketId());
        
        // Set ticket number
        google::protobuf::UInt32Value* ticket_number = new google::protobuf::UInt32Value();
        ticket_number->set_value(loadRecord.ticketNumber());
        Ticket.set_allocated_ticket_number(ticket_number);

        // Set total weight
        google::protobuf::FloatValue* total_weight = new google::protobuf::FloatValue();
        total_weight->set_value(loadRecord.weightTonnes());
        Ticket.set_allocated_total_weight(total_weight);
 
        // Set subtotals
        auto subtotalCount = loadRecord.subtotalCount();

        // add load records for each subtotal
        for (uint32_t x=1; x<=subtotalCount; x++) {
            cpmticket::Ticket_Subtotal* ticket_subtotal;
            ticket_subtotal = Ticket.add_subtotals();
            const auto& subtotal = loadRecord.getSubtotalByIndex(x);

            // Set start time
            {
                timeUtc = subtotal.startTime.utcTime;
                localTimeOffset = tes_common_ais::getLocalTimeOffset(timeUtc).count();
                auto shmTime = subtotal.startTime.shmTime;
                auto secs =  std::chrono::duration_cast<std::chrono::seconds>(timeUtc.time_since_epoch()).count();
                cpmticket::Ticket_Timestamp* subtotalTimestamp = new cpmticket::Ticket_Timestamp();
                google::protobuf::Timestamp* subtotalStartTime = new google::protobuf::Timestamp();
                google::protobuf::Int32Value* subtotalStartTimeLocalTimeOffset = new google::protobuf::Int32Value;
                subtotalStartTime->set_seconds(secs);
                subtotalStartTimeLocalTimeOffset->set_value(localTimeOffset);
                google::protobuf::UInt32Value* subtotalShm = new google::protobuf::UInt32Value;
                subtotalShm->set_value(shmTime);
                subtotalTimestamp->set_allocated_time(subtotalStartTime);
                subtotalTimestamp->set_allocated_hour_meter(subtotalShm);
                subtotalTimestamp->set_allocated_local_time_offset(subtotalStartTimeLocalTimeOffset);
                ticket_subtotal->set_allocated_start_time(subtotalTimestamp);

                // check if ticket start time needs to be replaced
                if (secs < secsTicketStart) {
                	secsTicketStart = secs;
                	shmTimeTicketStart = shmTime;
                	localTimeOffsetTicketStart = localTimeOffset;
                }
            }

            // Set end time
            {
                timeUtc = subtotal.endTime.utcTime;
                localTimeOffset = tes_common_ais::getLocalTimeOffset(timeUtc).count();
                auto shmTime = subtotal.endTime.shmTime;
                auto secs =  std::chrono::duration_cast<std::chrono::seconds>(timeUtc.time_since_epoch()).count();
                cpmticket::Ticket_Timestamp* subtotalTimestamp = new cpmticket::Ticket_Timestamp();
                google::protobuf::Timestamp* subtotalEndTime = new google::protobuf::Timestamp();
                google::protobuf::Int32Value* subtotalEndTimeLocalTimeOffset = new google::protobuf::Int32Value;
                subtotalEndTime->set_seconds(secs);
                subtotalEndTimeLocalTimeOffset->set_value(localTimeOffset);
                google::protobuf::UInt32Value* subtotalShm = new google::protobuf::UInt32Value;
                subtotalShm->set_value(shmTime);
                subtotalTimestamp->set_allocated_time(subtotalEndTime);
                subtotalTimestamp->set_allocated_hour_meter(subtotalShm);
                subtotalTimestamp->set_allocated_local_time_offset(subtotalEndTimeLocalTimeOffset);
                ticket_subtotal->set_allocated_end_time(subtotalTimestamp);
            }

            // Set truck id
            google::protobuf::UInt32Value* truck_id = new google::protobuf::UInt32Value;
            truck_id->set_value(subtotal.truckId);
            ticket_subtotal->set_allocated_truck_id(truck_id);

            // Set truck name
            ticket_subtotal->set_truck_name(subtotal.truckName);

            // Set truck target weight
            google::protobuf::FloatValue* target_wt = new google::protobuf::FloatValue;
            target_wt->set_value(subtotal.truckTargetWeightTonnes);
            ticket_subtotal->set_allocated_truck_target_weight(target_wt);

            // Set material id
            google::protobuf::UInt32Value* material_id = new google::protobuf::UInt32Value;
            material_id->set_value(subtotal.materialId);
            ticket_subtotal->set_allocated_material_id(material_id);

            // Set material name
            ticket_subtotal->set_material_name(subtotal.materialName);

            // Set material density
            google::protobuf::FloatValue* material_density = new google::protobuf::FloatValue;
            material_density->set_value(subtotal.materialDensity);
            ticket_subtotal->set_allocated_material_density(material_density);

            // Set custom tags
            std::string custom1 = (!subtotal.customListName1.empty()) ? (subtotal.customListName1 + ": " + subtotal.tag1) : subtotal.tag1;
            std::string custom2 = (!subtotal.customListName2.empty()) ? (subtotal.customListName2 + ": " + subtotal.tag2) : subtotal.tag2;
            std::string custom3 = (!subtotal.customListName3.empty()) ? (subtotal.customListName3 + ": " + subtotal.tag3) : subtotal.tag3;
            std::string custom4 = (!subtotal.customListName4.empty()) ? (subtotal.customListName4 + ": " + subtotal.tag4) : subtotal.tag4;

            ticket_subtotal->set_tag_1(custom1);
            ticket_subtotal->set_tag_2(custom2);
            ticket_subtotal->set_tag_3(custom3);
            ticket_subtotal->set_tag_4(custom4);

            // Set subtotal weight
            google::protobuf::FloatValue* subtotal_weight = new google::protobuf::FloatValue;
            subtotal_weight->set_value(subtotal.weightTonnes());
            ticket_subtotal->set_allocated_subtotal_weight(subtotal_weight);

            // Set Measurements (passes)
            for (const auto& p : subtotal.passes()) {
                cpmticket::Ticket_Measurement* pass;
                pass = ticket_subtotal->add_passes();

                // Set time
                auto timeUtc = p.time.utcTime;
                auto shmTime = p.time.shmTime;
                auto secs =  std::chrono::duration_cast<std::chrono::seconds>(timeUtc.time_since_epoch()).count();
                localTimeOffset = tes_common_ais::getLocalTimeOffset(timeUtc).count();
                cpmticket::Ticket_Timestamp* passTimestamp = new cpmticket::Ticket_Timestamp();
                google::protobuf::Timestamp* passTime = new google::protobuf::Timestamp();
                google::protobuf::Int32Value* passTimeLocalTimeOffset = new google::protobuf::Int32Value;
                passTime->set_seconds(secs);
                passTimeLocalTimeOffset->set_value(localTimeOffset);
                google::protobuf::UInt32Value* passShm = new google::protobuf::UInt32Value;
                passShm->set_value(shmTime);
                passTimestamp->set_allocated_time(passTime);
                passTimestamp->set_allocated_hour_meter(passShm);
                passTimestamp->set_allocated_local_time_offset(passTimeLocalTimeOffset);
                pass->set_allocated_time(passTimestamp);

                // Set weight
                google::protobuf::FloatValue* wt = new google::protobuf::FloatValue;
                wt->set_value(p.weightTonnes);
                pass->set_allocated_weight(wt);

                // Set accuracy
                auto accuracy = p.getAccuracy();
                if (accuracy == LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW) {
                    pass->set_accuracy(cpmticket::Ticket_Measurement_ACCURACY_LOW);
                }
                else if (accuracy == LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED) {
                    pass->set_accuracy(cpmticket::Ticket_Measurement_ACCURACY_MEDIUM);
                }
                else if (accuracy == LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH) {
                    pass->set_accuracy(cpmticket::Ticket_Measurement_ACCURACY_HIGH);
                }
                else {
                    pass->set_accuracy(cpmticket::Ticket_Measurement_ACCURACY_NONE);
                }

            }
        }

        // Set time and shm that this ticket started
        {
           cpmticket::Ticket_Timestamp* ticketTimestamp = new cpmticket::Ticket_Timestamp();
           google::protobuf::Timestamp* ticketStartTime = new google::protobuf::Timestamp();
           ticketStartTime->set_seconds(secsTicketStart);
           google::protobuf::Int32Value* ticketLocalTimeOffset = new google::protobuf::Int32Value;
           ticketLocalTimeOffset->set_value(localTimeOffsetTicketStart);
           google::protobuf::UInt32Value* ticketShm = new google::protobuf::UInt32Value;
           ticketShm->set_value(shmTimeTicketStart);
           ticketTimestamp->set_allocated_time(ticketStartTime);
           ticketTimestamp->set_allocated_hour_meter(ticketShm);
           ticketTimestamp->set_allocated_local_time_offset(ticketLocalTimeOffset);
           Ticket.set_allocated_start_time(ticketTimestamp);
        }

        // Set time and shm that this ticket ended (same as load store time)
        {
            timeUtc = loadRecord.storeTime.utcTime;
            int16_t localTimeOffsetTicketEnd = tes_common_ais::getLocalTimeOffset(timeUtc).count();
            auto shmTimeTicketEnd = loadRecord.storeTime.shmTime;
            auto secsTicketEnd =  std::chrono::duration_cast<std::chrono::seconds>(timeUtc.time_since_epoch()).count();
            cpmticket::Ticket_Timestamp* ticketTimestamp = new cpmticket::Ticket_Timestamp();
            google::protobuf::Timestamp* ticketEndTime = new google::protobuf::Timestamp();
            ticketEndTime->set_seconds(secsTicketEnd);
            google::protobuf::Int32Value* ticketLocalTimeOffset = new google::protobuf::Int32Value;
            ticketLocalTimeOffset->set_value(localTimeOffsetTicketEnd);
            google::protobuf::UInt32Value* ticketShm = new google::protobuf::UInt32Value;
            ticketShm->set_value(shmTimeTicketEnd);
            ticketTimestamp->set_allocated_time(ticketEndTime);
            ticketTimestamp->set_allocated_hour_meter(ticketShm);
            ticketTimestamp->set_allocated_local_time_offset(ticketLocalTimeOffset);
            Ticket.set_allocated_end_time(ticketTimestamp);
        }

        Ticket.SerializeToOstream(&os);
    }
};

#endif
