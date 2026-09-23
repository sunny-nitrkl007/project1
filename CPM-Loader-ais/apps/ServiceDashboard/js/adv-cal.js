$(function() {
    let advCalibrationUpdateEnabled = false;
    
    let recentWeighResults = undefined;
    let weighCalibration = undefined;

    let recentWeightsPlotDiv = $('#panel-3d #recent-weights-plot')[0];    
    let recentWeightsPlotResizeTimeout;
    let recentWeightsPlotResizeObserver = new ResizeObserver(function(mutations) {
        // clear any existing timeout
        clearTimeout(recentWeightsPlotResizeTimeout);

        // set a new timeout to trigger Plotly.update after resizing stops
        recentWeightsPlotResizeTimeout = setTimeout(function() {
            // Update the layout of the existing Plotly plot
            Plotly.relayout(recentWeightsPlotDiv, { height: recentWeightsPlotDiv.clientHeight, width: recentWeightsPlotDiv.clientWidth });
        }, 500); //  timeout duration, change as needed
    });

    function initRecentWeighResultsPlot() {
        Plotly.newPlot(
            recentWeightsPlotDiv,
            [{ // Included Points
                type: 'scatter',
                mode: 'markers',
                name: 'Included',
                marker: { size: 15, color: 'green', symbol: 'x' },
                x: [],
                y: []
            },
            { // Excluded Points
                type: 'scatter',
                mode: 'markers',
                name: 'Excluded',
                marker: { size: 15, color: 'black', symbol: 'x' },
                x: [],
                y: []
            },
            { // Average
                type: 'scatter',
                mode: 'lines',
                name: 'Average',
                line: { width: 3, color: 'green', dash: 'solid' },
                x: [],
                y: []
            },
            { // Max
                type: 'scatter',
                mode: 'lines',
                name: 'Max',
                line: { width: 3, color: 'green', dash: 'dash' },
                x: [],
                y: []
            },
            { // Min
                type: 'scatter',
                mode: 'lines',
                name: 'Min',
                line: { width: 3, color: 'green', dash: 'dash' },
                x: [],
                y: []
            }],
            {
                title: 'Recent Weight Measurements',
                xaxis: { title: '', autorange: true },
                yaxis: { title: 'Weight (tonnes)', autorange: true },
            },
            {
                responsive: true
            })
            .then(function() {
                recentWeightsPlotResizeObserver.observe(recentWeightsPlotDiv, { attributes: true });
            });
    }

    function updateRecentWeighResultsPlot(data, stats) {
        const indices = data?.map((_, idx) => { return idx+1; });
        const weights = data?.map((entry) => { return entry.weight; });
        if ((indices !== undefined) &&
                (weights !== undefined) &&
                (indices.length == weights.length) &&
                (indices.length > 0)) {
            const refX = [indices[0]-1, indices[indices.length-1]+1];
            Plotly.restyle(recentWeightsPlotDiv, 
                    {
                        x: [
                            indices.slice(stats.idx),
                            indices.slice(0, stats.idx),
                            refX,
                            refX,
                            refX,
                        ],
                        y: [
                            weights.slice(stats.idx),
                            weights.slice(0, stats.idx),
                            [stats.ave, stats.ave],
                            [stats.ave+0.1, stats.ave+0.1],
                            [stats.ave-0.1, stats.ave-0.1],
                        ]
                    },
                    [0,1,2,3,4]);
        }
        else {
            Plotly.restyle(recentWeightsPlotDiv, 
                    {
                        x: [[], [], [], [], []],
                        y: [[], [], [], [], []]
                    },
                    [0,1,2,3,4]);
        }
    }

    function updateRecentWeighResultsTable(data, stats) {
        let tableElement = $('#panel-3d #recent-weights-table');
                
        tableElement.find('tbody').empty();
        data?.forEach((entry, idx) => {
            if (idx >= stats.idx) {
                tableElement.append(`<tr><td>Included</td><td>${entry.weight?.toFixed(3)}</td><td>${entry.dispWeight?.toFixed(2)}</td></tr>`);
            }
            else {
                tableElement.append(`<tr bgcolor='lightgray'><td>Excluded</td><td>${entry.weight?.toFixed(3)}</td><td>${entry.dispWeight?.toFixed(2)}</td></tr>`);
            }
        });

        tableElement.find('tfoot').html(`<tr><td>Average</td><td>${stats?.ave?.toFixed(3)}</td><td></td></tr>`);
    }
    
    let updateRecentWeighResultsDataTimeout;
    function updateRecentWeighResultsData() {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi',
            data: { 'requestType': 'FileRequest', 'fileRequested': 'RecentWeighResults' },
            timeout: 3000
        })
        .done(function(data) {
            recentWeighResults = data?.results;
        })
        .fail(function() {
            recentWeighResults = undefined;
        })
        .always(function() {
            if (advCalibrationUpdateEnabled) {
                updateRecentWeighResultsDataTimeout = setTimeout(updateRecentWeighResultsData, 5000);
                
                // Update Stats
                // Only include values that remain within 1 MPE
                const stats = recentWeighResults?.reduceRight((acc, entry, idx, ary) => {
                    const cnt = ary.length-idx;
                    const val = entry.weight;
                    const max = (val > acc.max) ? val : acc.max;
                    const min = (val < acc.min) ? val : acc.min;
                    const ave = (acc.ave * (cnt-1) + val) / cnt;
            
                    if (((max - ave) > 0.1) || ((ave - min) > 0.1)) {
                        acc.done = true;
                    }
                    else if (!acc.done) {
                        acc.max = max;
                        acc.min = min;
                        acc.ave = ave;
                        acc.idx = idx;
                    }
            
                    return acc;
                }, {max: -Infinity, min: Infinity, ave: 0, idx: undefined, done: false});
                
                updateRecentWeighResultsTable(recentWeighResults, stats);
                updateRecentWeighResultsPlot(recentWeighResults, stats);
            }
        });
    }

    let advCalAdjPlotDiv = $('#panel-3d #adv-cal-adj-plot')[0];
    let advCalAdjPlotResizeTimeout;
    let advCalAdjPlotResizeObserver = new ResizeObserver(function(mutations) {
        // clear any existing timeout
        clearTimeout(advCalAdjPlotResizeTimeout);

        // set a new timeout to trigger Plotly.update after resizing stops
        advCalAdjPlotResizeTimeout = setTimeout(function() {
            // Update the layout of the existing Plotly plot
            Plotly.relayout(advCalAdjPlotDiv, { height: advCalAdjPlotDiv.clientHeight, width: advCalAdjPlotDiv.clientWidth });
        }, 500); //  timeout duration, change as needed
    });

    function initAdvCalAdjPlot() {
        Plotly.newPlot(
            advCalAdjPlotDiv,
            [{ // Adjustments
                type: 'scatter',
                mode: 'markers',
                name: 'Adjustment',
                marker: { size: 15, color: 'green', symbol: 'circle-x-open' },
                x: [],
                y: []
            },
            { // Reference
                type: 'scatter',
                mode: 'lines',
                showlegend: false,
                line: { width: 1, color: 'green', dash: 'solid' },
                x: [],
                y: []
            },
            { // Reference
                type: 'scatter',
                mode: 'lines',
                name: 'Calibration',
                line: { width: 1, color: 'black', dash: 'dash' },
                x: [],
                y: []
            }],
            {
                title: 'Advanced Calibration Adjustment',
                xaxis: { title: 'Calibrated Weight (tonnes)', autorange: true },
                yaxis: { title: 'Adjusted Weight (tonnes)', autorange: true },
            },
            {
                responsive: true
            })
            .then(function() {
                advCalAdjPlotResizeObserver.observe(advCalAdjPlotDiv, { attributes: true });
            });
    }

    function updateAdvCalAdjPlot() {
        let calWeight = Number(weighCalibration?.calWeight);
        let advCalAdjust = weighCalibration?.advCalAdjust;
        
        if (isFinite(calWeight) && (advCalAdjust !== undefined)) {
            const refWeightLineX = [-0.5*calWeight, 2.0*calWeight];
            const refWeightLineY = refWeightLineX;

            const calWeightPointsX = advCalAdjust?.map((entry) => { return Number(entry?.[0]); });
            const calWeightPointsY = advCalAdjust?.map((entry) => { return Number(entry?.[1]); });
            
            let calWeightsLineX = [refWeightLineX[0]].concat(calWeightPointsX);
            calWeightsLineX.push(refWeightLineX[1]);

            let calWeightsLineY = [refWeightLineY[0]].concat(calWeightPointsY);
            calWeightsLineY.push(refWeightLineY[1]);

            Plotly.update(
                advCalAdjPlotDiv,
                {
                    x: [calWeightPointsX, calWeightsLineX, refWeightLineX],
                    y: [calWeightPointsY, calWeightsLineY, refWeightLineY]
                },
                {
                    annotations: [
                    ]
                },
                [0,1,2]
            );
        }
        else {
            Plotly.update(
                advCalAdjPlotDiv,
                {
                    x: [[],[],[]],
                    y: [[],[],[]]
                },
                {
                    annotations: [
                        { text: "No Data!", showarrow: false }
                    ]
                },
                [0,1,2]
            );
        }
    }
    
    function updateAdvCalAdjPlotForm() {
        let advCalAdjust = weighCalibration?.advCalAdjust;
        const calWeights = advCalAdjust?.map((entry) => { return Number(entry?.[0]); });
        const adjWeights = advCalAdjust?.map((entry) => { return Number(entry?.[1]); });

        let advCalAdjForm = $('#panel-3d #weight-adjust-form');

        if (calWeights && adjWeights) {
            let calWeight;
            let adjWeight;
            
            calWeight = calWeights?.[0];
            adjWeight = adjWeights?.[0];

            if (isFinite(calWeight) && isFinite(adjWeight)) {
                advCalAdjForm.find('#weight-adjust-input-1-cal').val(calWeight);
                advCalAdjForm.find('#weight-adjust-input-1-adj').val(adjWeight);
            }
            else {
                advCalAdjForm.find('input[id^=weight-adjust-input-1]').val('');
            }
            
            calWeight = calWeights?.[1];
            adjWeight = adjWeights?.[1];

            if (isFinite(calWeight) && isFinite(adjWeight)) {
                advCalAdjForm.find('#weight-adjust-input-2-cal').val(calWeight);
                advCalAdjForm.find('#weight-adjust-input-2-adj').val(adjWeight);
            }
            else {
                advCalAdjForm.find('input[id^=weight-adjust-input-2]').val('');
            }

            calWeight = calWeights?.[2];
            adjWeight = adjWeights?.[2];

            if (isFinite(calWeight) && isFinite(adjWeight)) {
                advCalAdjForm.find('#weight-adjust-input-3-cal').val(calWeight);
                advCalAdjForm.find('#weight-adjust-input-3-adj').val(adjWeight);
            }
            else {
                advCalAdjForm.find('input[id^=weight-adjust-input-3]').val('');
            }

            calWeight = calWeights?.[3];
            adjWeight = adjWeights?.[3];

            if (isFinite(calWeight) && isFinite(adjWeight)) {
                advCalAdjForm.find('#weight-adjust-input-4-cal').val(calWeight);
                advCalAdjForm.find('#weight-adjust-input-4-adj').val(adjWeight);
            }
            else {
                advCalAdjForm.find('input[id^=weight-adjust-input-4]').val('');
            }

            calWeight = calWeights?.[4];
            adjWeight = adjWeights?.[4];

            if (isFinite(calWeight) && isFinite(adjWeight)) {
                advCalAdjForm.find('#weight-adjust-input-5-cal').val(calWeight);
                advCalAdjForm.find('#weight-adjust-input-5-adj').val(adjWeight);
            }
            else {
                advCalAdjForm.find('input[id^=weight-adjust-input-5]').val('');
            }
        }
        else {
            advCalAdjForm.find('input[id^=weight-adjust-input]').val('');
        }
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
            if (advCalibrationUpdateEnabled) {
                requestWeighCalibrationTimeout = setTimeout(requestWeighCalibration, 2000);
            }
        })
        .always(function() {
            updateAdvCalAdjPlotForm();
            updateAdvCalAdjPlot();
        });
    }
    
    $('#panel-3d #weight-adjust-form').bind("reset", function(ev) {
        if (window.confirm('Are you sure you want to reset the calibration adjustment?')) {
            $.ajax({
                dataType: 'json',
                url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({'WeighCalibration_Wr': {"advCalAdjust": []}})
            })
            .done(function() {
                console.log('advCalAdjust write success.');
            })
            .fail(function() {
                console.error('advCalAdjust write failure.');
            })
            .always(function() {
                requestWeighCalibration();
            });
        }
        else {
            ev.preventDefault();
        }
    });
    
    $('#panel-3d #weight-adjust-form').submit(function(ev) {
        let calWeightAdjData = [];
        $(this).find('.input-group').each((index, item) => {
            let inputs = $(item).find('input');
            const calWeightText = inputs.eq(0).val();
            const adjWeightText = inputs.eq(1).val();
            const calWeight = calWeightText ? Number(calWeightText) : Number.NaN;
            const adjWeight = adjWeightText ? Number(adjWeightText) : Number.NaN;
            if (isFinite(calWeight) && isFinite(adjWeight)) {
                calWeightAdjData.push([calWeight, adjWeight]);
            }
        });
        
        //console.log(JSON.stringify({'WeighCalibration_Wr': {"advCalAdjust": calWeightAdjData}}));
        
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'WeighCalibration_Wr': {"advCalAdjust": calWeightAdjData}})
        })
        .done(function() {
            console.log('advCalAdjust write success.');
        })
        .fail(function() {
            console.error('advCalAdjust write failure.');
        })
        .always(function() {
            requestWeighCalibration();
        });
        ev.preventDefault();
    });

    $('#panel-3d .collapse').on('show.bs.collapse', function() {
        initRecentWeighResultsPlot();
        updateRecentWeighResultsTable();
        
        advCalibrationUpdateEnabled = true;
        updateRecentWeighResultsData();
        
        initAdvCalAdjPlot();
        requestWeighCalibration();
    });

    $('#panel-3d .collapse').on('hide.bs.collapse', function() {
        advCalibrationUpdateEnabled = false;
        
        updateRecentWeighResultsTable();
        
        recentWeightsPlotResizeObserver.disconnect();
        advCalAdjPlotResizeObserver.disconnect();
        
        clearTimeout(updateRecentWeighResultsDataTimeout);
        clearTimeout(requestWeighCalibrationTimeout);
    });
});

