(function(){
    'use strict'

    angular.module('SrcApp')
        .controller('BarChartController', BarChartController)

     BarChartController.$inject = ['ApiAnalyticsService'];
     function BarChartController(ApiAnalyticsService){
        var vm = this;


        vm.chartOptions = {
            chart: {
                type: 'discreteBarChart',
                height: 350,
                margin : {
                    top: 20,
                    right: 20,
                    bottom: 50,
                    left: 55
                },
                x: function(d){return d.label;},
                y: function(d){return d.value;},
                showValues: true,
                valueFormat: function(d){
                    return d3.format(',.4f')(d);
                },
                duration: 500,
                xAxis: {
                    axisLabel: 'X Axis'
                },
                yAxis: {
                    axisLabel: 'Y Axis',
                    axisLabelDistance: -10
                }
            }
        };

        vm.chartData = [
            {
                key: "Cumulative Return",
                values: [
//                    {
//                        "label" : "A" ,
//                        "value" : -29.765957771107
//                    } ,
//                    {
//                        "label" : "B" ,
//                        "value" : 0
//                    } ,
//                    {
//                        "label" : "C" ,
//                        "value" : 32.807804682612
//                    } ,
//                    {
//                        "label" : "D" ,
//                        "value" : 196.45946739256
//                    } ,
//                    {
//                        "label" : "E" ,
//                        "value" : 0.19434030906893
//                    } ,
//                    {
//                        "label" : "F" ,
//                        "value" : -98.079782601442
//                    } ,
//                    {
//                        "label" : "G" ,
//                        "value" : -13.925743130903
//                    } ,
//                    {
//                        "label" : "H" ,
//                        "value" : -5.1387322875705
//                    }
                ]
            }
        ]
        ApiAnalyticsService.GetSpeedStats().then(function(res){
            var data = res.data;
            console.log(data);

         var newDataArray = [
                    {
                    "label" : "Illegal average speed" ,
                    "value" : data.illegal_avg
                    },
                    {
                    "label" : "Legal average speed" ,
                    "value" : data.legal_avg
                    },
                    {
                    "label" : "Main average speed" ,
                    "value" : data.main_avg
                    }
                ];
         vm.chartData[0].values = newDataArray;
        });

     }
})();