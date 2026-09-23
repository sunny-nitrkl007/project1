var selectFileText = 'select file to upload...';

$(function() {
    $('.open-folder-icon').html('&#x1f4c2;');
    
    $('#material-list-file-name').val(selectFileText);
    $('#material-list-file-submit').prop('disabled', true);
	
    $('#material-list-file-form').submit(function(ev) {
        let frm = $(this);
        let action = frm.attr('action');
        let method = frm.attr('method');
        $.ajax({
            url: action,
            type: method,
            data: new FormData(this),
            cache: false,
            contentType: false,
            processData: false
        })
        .done(function() {
            showSimplePopup('Success', 'Uploaded file.');
            $('#material-list-file-input').val('').change();
            console.log('file upload success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not upload file.');
            console.log('file upload fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });

    $('#truck-list-file-name').val(selectFileText);
    $('#truck-list-file-submit').prop('disabled', true);

    $('#truck-list-file-form').submit(function(ev) {
        let frm = $(this);
        let action = frm.attr('action');
        let method = frm.attr('method');
        $.ajax({
            url: action,
            type: method,
            data: new FormData(this),
            cache: false,
            contentType: false,
            processData: false
        })
        .done(function() {
            showSimplePopup('Success', 'Uploaded file.');
            $('#truck-list-file-input').val('').change();
            console.log('file upload success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not upload file.');
            console.log('file upload fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    
    $('#operator-id-list-file-name').val(selectFileText);
    $('#operator-id-list-file-submit').prop('disabled', true);

    $('#operator-id-list-file-form').submit(function(ev) {
        let frm = $(this);
        let action = frm.attr('action');
        let method = frm.attr('method');
        $.ajax({
            url: action,
            type: method,
            data: new FormData(this),
            cache: false,
            contentType: false,
            processData: false
        })
        .done(function() {
            showSimplePopup('Success', 'Uploaded file.');
            $('#operator-id-list-file-input').val('').change();
            console.log('file upload success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not upload file.');
            console.log('file upload fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });

    $('#custom-list-1-file-name').val(selectFileText);
    $('#custom-list-1-file-submit').prop('disabled', true);

    $('#custom-list-1-file-form').submit(function(ev) {
        let frm = $(this);
        let action = frm.attr('action');
        let method = frm.attr('method');
        $.ajax({
            url: action,
            type: method,
            data: new FormData(this),
            cache: false,
            contentType: false,
            processData: false
        })
        .done(function() {
            showSimplePopup('Success', 'Uploaded file.');
            $('#custom-list-1-file-input').val('').change();
            console.log('file upload success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not upload file.');
            console.log('file upload fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });

    $('#custom-list-2-file-name').val(selectFileText);
    $('#custom-list-2-file-submit').prop('disabled', true);

    $('#custom-list-2-file-form').submit(function(ev) {
        let frm = $(this);
        let action = frm.attr('action');
        let method = frm.attr('method');
        $.ajax({
            url: action,
            type: method,
            data: new FormData(this),
            cache: false,
            contentType: false,
            processData: false
        })
        .done(function() {
            showSimplePopup('Success', 'Uploaded file.');
            $('#custom-list-2-file-input').val('').change();
            console.log('file upload success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not upload file.');
            console.log('file upload fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });

    $('#custom-list-3-file-name').val(selectFileText);
    $('#custom-list-3-file-submit').prop('disabled', true);

    $('#custom-list-3-file-form').submit(function(ev) {
        let frm = $(this);
        let action = frm.attr('action');
        let method = frm.attr('method');
        $.ajax({
            url: action,
            type: method,
            data: new FormData(this),
            cache: false,
            contentType: false,
            processData: false
        })
        .done(function() {
            showSimplePopup('Success', 'Uploaded file.');
            $('#custom-list-3-file-input').val('').change();
            console.log('file upload success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not upload file.');
            console.log('file upload fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });

    $('#custom-list-4-file-name').val(selectFileText);
    $('#custom-list-4-file-submit').prop('disabled', true);

    $('#custom-list-4-file-form').submit(function(ev) {
        let frm = $(this);
        let action = frm.attr('action');
        let method = frm.attr('method');
        $.ajax({
            url: action,
            type: method,
            data: new FormData(this),
            cache: false,
            contentType: false,
            processData: false
        })
        .done(function() {
            showSimplePopup('Success', 'Uploaded file.');
            $('#custom-list-4-file-input').val('').change();
            console.log('file upload success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not upload file.');
            console.log('file upload fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    
    ShowOrHide();

    $('#tipoff-weight-adjust-form').submit(function(ev) {
        let command = {'TipoffWeightAdjustData_Wr': {}};
        let value;

        value = $('#tipoff-weight-1-input').val();
        if (value) {
            let num = Number(value);
            if (isFinite(num)) {
                command.TipoffWeightAdjustData_Wr.TipoffWeight1 = num;
            }
        }

        value = $('#weigh-range-weight-1-input').val();
        if (value) {
            let num = Number(value);
            if (isFinite(num)) {
                command.TipoffWeightAdjustData_Wr.WeighRangeWeight1 = num;
            }
        }

        value = $('#tipoff-weight-2-input').val();
        if (value) {
            let num = Number(value);
            if (isFinite(num)) {
                command.TipoffWeightAdjustData_Wr.TipoffWeight2 = num;
            }
        }

        value = $('#weigh-range-weight-2-input').val();
        if (value) {
            let num = Number(value);
            if (isFinite(num)) {
                command.TipoffWeightAdjustData_Wr.WeighRangeWeight2 = num;
            }
        }

        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify(command)
        })
        .done(function() {
            console.log('TipoffWeightAdjustData_Wr success.');
            $('#tipoff-weight-1-input').val('');
            $('#weigh-range-weight-1-input').val('');
            $('#tipoff-weight-2-input').val('');
            $('#weigh-range-weight-2-input').val('');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not set value.');
            console.log('TipoffWeightAdjustData_Wr fail.');
            $('#tipoff-weight-1-input').val('');
            $('#weigh-range-weight-1-input').val('');
            $('#tipoff-weight-2-input').val('');
            $('#weigh-range-weight-2-input').val('');
        })
        .always(function() {
        });
        ev.preventDefault();
    });

    $('#tipoff-weight-reset-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'TipoffWeightAdjustData_Reset': 1})
        })
        .done(function() {
            console.log('TipoffWeightAdjustData_Reset success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not reset.');
            console.log('TipoffWeightAdjustData_Reset fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    
    $('#udp-ip-address-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'UDP_Transfer_Details_Wr': {"udpTransferIpAddress": $('#desired-ip-address-input').val()}})
        })
        .done(function() {
            console.log('UDP Ip Address write success');
            document.getElementById('desired-ip-address-input').value = '';
        })
        .fail(function() {
            console.log('UDP Ip Address write fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });

    $('#udp-port-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'UDP_Transfer_Details_Wr': {"udpTransferPort": $('#desired-udp-port-input').val()}})
        })
        .done(function() {
            console.log('UDP Port write success');
            document.getElementById('desired-udp-port-input').value = '';
        })
        .fail(function() {
            console.log('UDP Port write fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    
    let el=document.getElementById('UDPEnabled');
    el.onclick=function() {
        let status = 1;
        if (document.querySelector('#UDPEnabled').innerHTML == 'Enable UDP Transfer') {
            document.querySelector('#UDPEnabled').innerHTML = 'Disable UDP Transfer';
            status = 1;
        }
        else {
            document.querySelector('#UDPEnabled').innerHTML = 'Enable UDP Transfer';
            status = 0;
        }
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'UDP_Transfer_Details_Wr': {'udpTransferEnabled': status}})
        })
        .done(function() {
            console.log('UDP enable success');
        })
        .fail(function() {
            console.log('UDP enable failure');
        })
        .always(function() {
        });
    }

    $('#mach-imu-pitch-offset-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'MachImuPitchOffset': Number($('#mach-imu-pitch-offset-input').val())})
        })
        .done(function() {
            $('#mach-imu-pitch-offset-input').val('').change();
            $('#mach-imu-pitch-offset-value').text('?');
            console.log('set MachImuPitchOffset success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not set value.');
            console.log('set MachImuPitchOffset fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });

    // Printer Test
    $('#print-test-button-1').click(function() { printTest(1); });
    $('#print-test-button-2').click(function() { printTest(2); });
    $('#print-test-button-3').click(function() { printTest(3); });

    function printTest(numCopies) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'Test_Prt': Math.floor(numCopies)})
        })
        .done(function() {
            console.log('Print test request success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not request print test.');
            console.log('Print test request fail.');
        })
        .always(function() {
        });
    }

    function showPopup(btn, header, body) {
        btn.button('loading');
        $('#pop-up-header').html(header);
        $('#pop-up-body').html(body);
        $('#pop-up').modal('show');
        $('#pop-up').one('hidden.bs.modal', function() {
            btn.button('reset');
        });
    };

    function showSimplePopup(header, body) {
        $('#pop-up-header').html(header);
        $('#pop-up-body').html(body);
        $('#pop-up').modal('show');
    };

    function ShowOrHide() {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi',
            data: { 'requestType': 'FileRequest', 'fileRequested': 'UI_SHOW_FEATURE_CONFIG' },
        })
        .done(function(data) {
            if (data?.OperatorIdCsv?.supported) {
                $("#ShoworHideOperatorId").attr("style", "display:block");
            }
            else {
                $("#ShoworHideOperatorId").attr("style", "display:none");
            }
            if (data?.PayloadLFT?.supported && data?.PayloadLFT?.installed !== false) {
                $("#maximum-pitch-form").attr("style", "display:block");
                $("#minimum-pitch-form").attr("style", "display:block");
                $("#maximum-roll-form").attr("style", "display:block");
            }
            else {
                $("#maximum-pitch-form").attr("style", "display:none");
                $("#minimum-pitch-form").attr("style", "display:none");
                $("#maximum-roll-form").attr("style", "display:none");
            }
            if (data?.TipOffAssist?.supported) {
                $("#panel-3a").attr("style", "display:block");
            }
            else {
                $("#panel-3a").attr("style", "display:none");
            }
        })
        .fail(function() {
            console.log("failed to hide operator id or TOA or IMU");
            setTimeout(ShowOrHide, 1000);
        })
        .always(function() {
        });
    }

    let updateTipoffAdjustEnabled = false;
    let updateTipoffAdjustTimeout;
    function updateTipoffAdjust() {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi',
            data: { 'requestType': 'ParameterRequest2', 'paramsRequested': 'TipoffWeightAdjustData,MachImuPitchOffset' },
            timeout: 3000
        })
        .done(function(data) {
            $('[id^=tipoff-weight-units-]').text(data.TipoffWeightAdjustData.units.value);
            $('#tipoff-offset-value').text(Number(data.TipoffWeightAdjustData.offset.value).toFixed(3));
            $('#tipoff-slope-value').text(Number(data.TipoffWeightAdjustData.slope.value).toFixed(3));
            $('#tipoff-adjust-status').text(data.TipoffWeightAdjustData.status.value);
            $('#mach-imu-pitch-offset-value').text(Number(data.MachImuPitchOffset.value).toFixed(3));
        })
        .fail(function() {
            $('[id^=tipoff-weight-units-]').text('tonnes');
            $('#tipoff-offset-value').text('?');
            $('#tipoff-slope-value').text('?');
            $('#tipoff-adjust-status').text('?');
            $('#mach-imu-pitch-offset-value').text('?');
        })
        .always(function() {
            if (updateTipoffAdjustEnabled) {
                updateTipoffAdjustTimeout = setTimeout(updateTipoffAdjust, 1000);
            }
        });
    };

    $('#panel-3a .collapse').on('show.bs.collapse', function() {
        updateTipoffAdjustEnabled = true;
        updateTipoffAdjust();
    });

    $('#panel-3a .collapse').on('hide.bs.collapse', function() {
        updateTipoffAdjustEnabled = false;
        clearTimeout(updateTipoffAdjustTimeout);
    });

    let udpUpdateEnabled = false;
    let udpUpdateTimeout;
    function udpUpdate() {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi',
            data: { 'requestType': 'ParameterRequest2', 'paramsRequested': 'UDP_Transfer_Details' },
            timeout: 3000
        })
        .done(function(data) {
            document.getElementById('desired-ip-address-value').innerHTML = data.UDP_Transfer_Details.udpTransferIpAddress.value;
            document.getElementById('desired-udp-port-value').innerHTML = data.UDP_Transfer_Details.udpTransferPort.value;
            if (data.UDP_Transfer_Details.udpTransferEnabled.value == 1) {
                document.querySelector('#UDPEnabled').innerHTML = 'Disable UDP Transfer';
            }
            else {
                document.querySelector('#UDPEnabled').innerHTML = 'Enable UDP Transfer';
            }
        })
        .fail(function() {
            $('#desired-ip-address-value').text('?');
            $('#desired-udp-port-value').text('?');
        })
        .always(function() {
            if (udpUpdateEnabled) {
                udpUpdateTimeout = setTimeout(udpUpdate, 1000);
            }
        });
    };

    $('#panel-3b .collapse').on('show.bs.collapse', function() {
        udpUpdateEnabled = true;
        udpUpdate();
    });

    $('#panel-3b .collapse').on('hide.bs.collapse', function() {
        udpUpdateEnabled = false;
        clearTimeout(udpUpdateTimeout);
    });

    $('#material-list-file-input').change(function() {
        if ((this.files != null) && (this.files.length > 0)) {
            if (this.files.length > 1) {
                $('#material-list-file-name').val(selectFileText);
                $('#material-list-file-submit').prop('disabled', true);
                showSimplePopup("Error", "Multi-file selection not supported.");
            }
            else {
                if (this.files[0].size > 51200) {
                    $('#material-list-file-name').val(selectFileText);
                    $('#material-list-file-submit').prop('disabled', true);
                    showSimplePopup("Error", "File size > 50k.");
                }
                else {
                    $('#material-list-file-name').val(this.files[0].name);
                    $('#material-list-file-submit').prop('disabled', false);
                }
            }
        }
        else {
            $('#material-list-file-name').val(selectFileText);
            $('#material-list-file-submit').prop('disabled', true);
        }
    });

    $('#truck-list-file-input').change(function() {
        if ((this.files != null) && (this.files.length > 0)) {
            if (this.files.length > 1) {
                $('#truck-list-file-name').val(selectFileText);
                $('#truck-list-file-submit').prop('disabled', true);
                showSimplePopup("Error", "Multi-file selection not supported.");
            }
            else {
                if (this.files[0].size > 51200) {
                    $('#truck-list-file-name').val(selectFileText);
                    $('#truck-list-file-submit').prop('disabled', true);
                    showSimplePopup("Error", "File size > 50k.");
                }
                else {
                    $('#truck-list-file-name').val(this.files[0].name);
                    $('#truck-list-file-submit').prop('disabled', false);
                }
            }
        }
        else {
            $('#truck-list-file-name').val(selectFileText);
            $('#truck-list-file-submit').prop('disabled', true);
        }
    });

    $('#operator-id-list-file-input').change(function() {
        if ((this.files != null) && (this.files.length > 0)) {
            if (this.files.length > 1) {
                $('#operator-id-list-file-name').val(selectFileText);
                $('#operator-id-list-file-submit').prop('disabled', true);
                showSimplePopup("Error", "Multi-file selection not supported.");
            }
            else {
                if (this.files[0].size > 51200) {
                    $('#operator-id-list-file-name').val(selectFileText);
                    $('#operator-id-list-file-submit').prop('disabled', true);
                    showSimplePopup("Error", "File size > 50k.");
                }
                else {
                    $('#operator-id-list-file-name').val(this.files[0].name);
                    $('#operator-id-list-file-submit').prop('disabled', false);
                }
            }
        }
        else {
            $('#operator-id-list-file-name').val(selectFileText);
            $('#operator-id-list-file-submit').prop('disabled', true);
        }
    });

    $('#custom-list-1-file-input').change(function() {
        if ((this.files != null) && (this.files.length > 0)) {
            if (this.files.length > 1) {
                $('#custom-list-1-file-name').val(selectFileText);
                $('#custom-list-1-file-submit').prop('disabled', true);
                showSimplePopup("Error", "Multi-file selection not supported.");
            }
            else {
                if (this.files[0].size > 51200) {
                    $('#custom-list-1-file-name').val(selectFileText);
                    $('#custom-list-1-file-submit').prop('disabled', true);
                    showSimplePopup("Error", "File size > 50k.");
                }
                else {
                    $('#custom-list-1-file-name').val(this.files[0].name);
                    $('#custom-list-1-file-submit').prop('disabled', false);
                }
            }
        }
        else {
            $('#custom-list-1-file-name').val(selectFileText);
            $('#custom-list-1-file-submit').prop('disabled', true);
        }
    });

    $('#custom-list-2-file-input').change(function() {
        if ((this.files != null) && (this.files.length > 0)) {
            if (this.files.length > 1) {
                $('#custom-list-2-file-name').val(selectFileText);
                $('#custom-list-2-file-submit').prop('disabled', true);
                showSimplePopup("Error", "Multi-file selection not supported.");
            }
            else {
                if (this.files[0].size > 51200) {
                    $('#custom-list-2-file-name').val(selectFileText);
                    $('#custom-list-2-file-submit').prop('disabled', true);
                    showSimplePopup("Error", "File size > 50k.");
                }
                else {
                    $('#custom-list-2-file-name').val(this.files[0].name);
                    $('#custom-list-2-file-submit').prop('disabled', false);
                }
            }
        }
        else {
            $('#custom-list-2-file-name').val(selectFileText);
            $('#custom-list-2-file-submit').prop('disabled', true);
        }
    });

    $('#custom-list-3-file-input').change(function() {
        if ((this.files != null) && (this.files.length > 0)) {
            if (this.files.length > 1) {
                $('#custom-list-3-file-name').val(selectFileText);
                $('#custom-list-3-file-submit').prop('disabled', true);
                showSimplePopup("Error", "Multi-file selection not supported.");
            }
            else {
                if (this.files[0].size > 51200) {
                    $('#custom-list-3-file-name').val(selectFileText);
                    $('#custom-list-3-file-submit').prop('disabled', true);
                    showSimplePopup("Error", "File size > 50k.");
                }
                else {
                    $('#custom-list-3-file-name').val(this.files[0].name);
                    $('#custom-list-3-file-submit').prop('disabled', false);
                }
            }
        }
        else {
            $('#custom-list-3-file-name').val(selectFileText);
            $('#custom-list-3-file-submit').prop('disabled', true);
        }
    });

    $('#custom-list-4-file-input').change(function() {
        if ((this.files != null) && (this.files.length > 0)) {
            if (this.files.length > 1) {
                $('#custom-list-4-file-name').val(selectFileText);
                $('#custom-list-4-file-submit').prop('disabled', true);
                showSimplePopup("Error", "Multi-file selection not supported.");
            }
            else {
                if (this.files[0].size > 51200) {
                    $('#custom-list-4-file-name').val(selectFileText);
                    $('#custom-list-4-file-submit').prop('disabled', true);
                    showSimplePopup("Error", "File size > 50k.");
                }
                else {
                    $('#custom-list-4-file-name').val(this.files[0].name);
                    $('#custom-list-4-file-submit').prop('disabled', false);
                }
            }
        }
        else {
            $('#custom-list-4-file-name').val(selectFileText);
            $('#custom-list-4-file-submit').prop('disabled', true);
        }
    });
});

