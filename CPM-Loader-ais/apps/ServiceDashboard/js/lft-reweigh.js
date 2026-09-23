$(function() {
    let reweighWarningsUpdateEnabled = false;

    let weighConfiguration = undefined;
    let weighCalibration = undefined;
    let imuData = undefined;

    let imuPlotDiv = $('#panel-3c #imu-plot')[0];
    let imuPlotDivResizeTimeout;
    let imuPlotDivObserver = new ResizeObserver(function(mutations) {
        // clear any existing timeout
        clearTimeout(imuPlotDivResizeTimeout);

        // set a new timeout to trigger Plotly.update after resizing stops
        imuPlotDivResizeTimeout = setTimeout(function() {
            // Update the layout of the existing Plotly plot
            Plotly.relayout(imuPlotDiv, { height: imuPlotDiv.clientHeight, width: imuPlotDiv.clientWidth });
        }, 500); //  timeout duration, change as needed
    });

    $('#panel-3c #minimum-velocity-form').submit(function(ev) {
        let inputElement = $('#panel-3c #minimum-velocity-input');
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'WeighConfiguration_Wr': {"reweighMinLiftCylVel": Number(inputElement.val())}})
        })
        .done(function() {
            console.log('reweighMinLiftCylVel write success.');
        })
        .fail(function() {
            console.error('reweighMinLiftCylVel write failure.');
        })
        .always(function() {
            inputElement.val('');
            requestWeighConfiguration();
        });
        ev.preventDefault();
    });

    $('#panel-3c #maximum-pitch-form').submit(function(ev) {
        let inputElement = $('#panel-3c #maximum-pitch-input');
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'WeighConfiguration_Wr': {"reweighMaxPitch": Number(inputElement.val())}})
        })
        .done(function() {
            console.log('reweighMaxPitch write success.');
        })
        .fail(function() {
            console.error('reweighMaxPitch write failure.');
        })
        .always(function() {
            inputElement.val('');
            requestWeighConfiguration();
        });
        ev.preventDefault();
    });

    $('#panel-3c #minimum-pitch-form').submit(function(ev) {
        let inputElement = $('#panel-3c #minimum-pitch-input');
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'WeighConfiguration_Wr': {"reweighMinPitch": Number(inputElement.val())}})
        })
        .done(function() {
            console.log('reweighMinPitch write success.');
        })
        .fail(function() {
            console.error('reweighMinPitch write failure.');
        })
        .always(function() {
            inputElement.val('');
            requestWeighConfiguration();
        });
        ev.preventDefault();
    });

    $('#panel-3c #maximum-roll-form').submit(function(ev) {
        let inputElement = $('#panel-3c #maximum-roll-input');
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'WeighConfiguration_Wr': {"reweighMaxAbsRoll": Number(inputElement.val())}})
        })
        .done(function() {
            console.log('reweighMaxAbsRoll write success.');
        })
        .fail(function() {
            console.error('reweighMaxAbsRoll write failure.');
        })
        .always(function() {
            inputElement.val('');
            requestWeighConfiguration();
        });
        ev.preventDefault();
    });

    $('#panel-3c #imu-comp-enable-form').submit(function(ev) {
        let inputElement = $('#panel-3c #imu-comp-enable-submit');
        let inputValue = inputElement.text();
        if (inputValue === 'Disable') {
            inputValue = false;
        }
        else if (inputValue === 'Enable') {
            inputValue = true;
        }
        else {
            inputValue = undefined;
        }
        if (inputValue !== undefined) {
            $.ajax({
                dataType: 'json',
                url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({'WeighConfiguration_Wr': {"imuCompEnabled": inputValue}})
            })
            .done(function() {
                console.log('imuCompEnabled write success.');
            })
            .fail(function() {
                console.error('imuCompEnabled write failure.');
            })
            .always(function() {
                inputElement.text('...');
                $('#panel-3c #imu-comp-enable-value').text('...');
                requestWeighConfiguration();
            });
        }
        else {
            console.error('imuCompEnabled write value unknown.');
        }
        ev.preventDefault();
    });

    function initIMUPlot() {
        weighConfiguration = undefined;
        weighCalibration = undefined;
        imuData = undefined;
        Plotly.newPlot(
            imuPlotDiv,
            [{ // Current IMU Position
                type: 'scatter',
                name: 'Current',
                marker: { size: 15, color: 'green', symbol: 'cross' },
                line: { width: 0 },
                x: [],
                y: []
            },
            { // IMU Empty Calibration IMU Position
                type: 'scatter',
                name: 'Empty Calibration',
                marker: { size: 15, color: 'black', symbol: 'triangle-up' },
                line: { width: 0 },
                x: [],
                y: []
            },
            { // IMU Full Calibration IMU Position
                type: 'scatter',
                name: 'Full Calibration',
                marker: { size: 15, color: 'black', symbol: 'triangle-down' },
                line: { width: 0 },
                x: [],
                y: []
            }],
            {
                title: 'Pitch and Roll',
                plot_bgcolor: 'lightgray',
                xaxis: { title: 'Roll (deg)', gridcolor: 'lightgray', autorange: true },
                yaxis: { title: 'Pitch (deg)', gridcolor: 'lightgray', autorange: true, scaleanchor: 'x', scaleratio: 1 },
            },
            {
                responsive: true
            })
            .then(function() {
                imuPlotDivObserver.observe(imuPlotDiv, { attributes: true });
            });
    }

    function updateIMUPlot() {
        let pitch = Number(imuData?.machinePitch?.value);
        let roll = Number(imuData?.machineRoll?.value);
        let emptyCalPitch = Number(weighCalibration?.slowRaiseEmptyPitch);
        let emptyCalRoll = Number(weighCalibration?.slowRaiseEmptyRoll);
        let fullCalPitch = Number(weighCalibration?.slowRaiseFullPitch);
        let fullCalRoll = Number(weighCalibration?.slowRaiseFullRoll);
        let reweighMaxPitch = Number(weighConfiguration?.reweighMaxPitch);
        let reweighMinPitch = Number(weighConfiguration?.reweighMinPitch);
        let reweighMaxAbsRoll = Number(weighConfiguration?.reweighMaxAbsRoll);
        
        if (isFinite(pitch) && isFinite(roll) &&
            isFinite(emptyCalPitch) && isFinite(emptyCalRoll) &&
            isFinite(fullCalPitch) && isFinite(fullCalRoll) &&
            isFinite(reweighMaxPitch) && isFinite(reweighMinPitch) &&
            isFinite(reweighMaxAbsRoll)) {
            
            Plotly.update(
                imuPlotDiv,
                {
                    x: [[roll],[emptyCalRoll],[fullCalRoll]],
                    y: [[pitch],[emptyCalPitch],[fullCalPitch]]
                },
                {
                    annotations: [
                    ],
                    shapes: [
                        { layer: 'below', type: 'rect', x0: fullCalRoll-reweighMaxAbsRoll, x1: fullCalRoll+reweighMaxAbsRoll, y0: fullCalPitch+reweighMinPitch, y1: fullCalPitch+reweighMaxPitch, line: { color: 'red', dash: 'dash'}, fillcolor: 'white' },
                        { layer: 'below', type: 'circle', x0: -2, x1: +2, y0: -2, y1: +2, line: { width: 0 }, fillcolor: 'green', opacity: 0.2 },
                    ]
                },
                [0,1,2]
            );
        }
        else {
            Plotly.update(
                imuPlotDiv,
                {
                    x: [[],[],[]],
                    y: [[],[],[]]
                },
                {
                    annotations: [
                        { text: "No Data!", showarrow: false }
                    ],
                    shapes: [
                    ]
                },
                [0,1,2]
            );
        }
    }

    let requestWeighConfigurationTimeout;
    function requestWeighConfiguration() {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi',
            data: { 'requestType': 'FileRequest', 'fileRequested': 'WeighConfiguration' },
            timeout: 3000
        })
        .done(function(data) {
            let value;
            value = Number(data?.parameters?.reweighMaxPitch);
            $('#panel-3c #maximum-pitch-value').text(isFinite(value) ? value.toFixed(1) : '?');
            value = Number(data?.parameters?.reweighMinPitch);
            $('#panel-3c #minimum-pitch-value').text(isFinite(value) ? value.toFixed(1) : '?');
            value = Number(data?.parameters?.reweighMaxAbsRoll);
            $('#panel-3c #maximum-roll-value').text(isFinite(value) ? value.toFixed(1) : '?');
            value = Number(data?.parameters?.reweighMinLiftCylVel);
            $('#panel-3c #minimum-velocity-value').text(isFinite(value) ? value.toFixed(1) : '?');
            value = data?.parameters?.imuCompEnabled;
            if (value === undefined) {
              $('#panel-3c #imu-comp-enable-value').text('?');
              $('#panel-3c #imu-comp-enable-submit').text('?').prop("disabled", true);
            }
            else if (value) {
              $('#panel-3c #imu-comp-enable-value').text('enabled');
              $('#panel-3c #imu-comp-enable-submit').text('Disable').prop("disabled", false);
            }
            else {
              $('#panel-3c #imu-comp-enable-value').text('disabled');
              // Don't allow enabling imu-comp-enable at this time.
              //$('#panel-3c #imu-comp-enable-submit').text('Enable').prop("disabled", false);
              $('#panel-3c #imu-comp-enable-submit').text('Not Supported').prop("disabled", true);
            }
            weighConfiguration = data?.parameters;
        })
        .fail(function() {
            $('#panel-3c #maximum-pitch-value').text('?');
            $('#panel-3c #minimum-pitch-value').text('?');
            $('#panel-3c #maximum-roll-value').text('?');
            $('#panel-3c #minimum-velocity-value').text('?');
            $('#panel-3c #imu-comp-enable-value').text('?');
            $('#panel-3c #imu-comp-enable-submit').text('?').prop("disabled", true);
            weighConfiguration = undefined;
            if (reweighWarningsUpdateEnabled) {
                requestWeighConfigurationTimeout = setTimeout(requestWeighConfiguration, 2000);
            }
        })
        .always(function() {
            updateIMUPlot();
        });
    }

    let requestWeighCalibrationTimeout;
    function requestWeighCalibration() {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi',
            data: { 'requestType': 'FileRequest', 'fileRequested': 'WeighCalibration' },
            timeout: 3000
        })
        .done(function(data) {
            weighCalibration = data?.parameters;
        })
        .fail(function() {
            weighConfiguration = undefined;
            if (reweighWarningsUpdateEnabled) {
                requestWeighCalibrationTimeout = setTimeout(requestWeighCalibration, 2000);
            }
        })
        .always(function() {
            updateIMUPlot();
        });
    }

    let updateReweighWarningsDataTimeout;
    function updateReweighWarningsData() {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi',
            data: { 'requestType': 'ParameterRequest2', 'paramsRequested': 'IMUData' },
            timeout: 3000
        })
        .done(function(data) {
            imuData = data?.IMUData;
        })
        .fail(function() {
            imuData = undefined;
        })
        .always(function() {
            if (reweighWarningsUpdateEnabled) {
                updateReweighWarningsDataTimeout = setTimeout(updateReweighWarningsData, 1000);
            }
            updateIMUPlot();
        });
    };

    $('#panel-3c .collapse').on('show.bs.collapse', function() {
        initIMUPlot();
        reweighWarningsUpdateEnabled = true;
        updateReweighWarningsData();
        requestWeighConfiguration();
        requestWeighCalibration();
    });

    $('#panel-3c .collapse').on('hide.bs.collapse', function() {
        reweighWarningsUpdateEnabled = false;
        imuPlotDivObserver.disconnect();
        clearTimeout(requestWeighConfigurationTimeout);
        clearTimeout(requestWeighCalibrationTimeout);
        clearTimeout(updateReweighWarningsDataTimeout);
    });
});


