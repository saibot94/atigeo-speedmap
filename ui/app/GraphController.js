(function () {
	'use strict';

		angular.module('SrcApp')
			.controller('GraphController', GraphController);

		GraphController.$inject = ['$scope', 'ApiCarDataService'];

		function GraphController($scope, ApiCarDataService) {
			var vm = this;

			vm.lineGraphOptions = {
				chart: {
					type: 'lineChart', 
					height: 250,
					margin :{ 
						top: 30,
						bottom: 50,
						left: 20,
						right: 20
					},
		            x: function(d){ return d.x; },
	                y: function(d){ return d.y; },
	                useInteractiveGuideline: true,	
                    xAxis: {
                    	axisLabel: 'Time (ms)'
	                },
	                yAxis: {
	                    axisLabel: 'Speed (kmh)',
	                    tickFormat: function(d){
	                        return d3.format('.02f')(d);
	                    },
	                    axisLabelDistance: -10
	                },
	                callback: function(chart){
	                  
	                }
				},
	            title: {
                	enable: true,
                	text: 'Live velocity data'
            	},
            	subtitle: {
                	enable: true,
                	text: 'Agg. data throughout the city',
                	css: {
	                    'text-align': 'center',
     	               'margin': '10px 13px 0px 7px'
        	        }
            	}

			};
		
            ApiCarDataService.GetPoints().then(function(res) {
                console.log(res.data.points);
                vm.lineGraphData = createDataPoints(res.data.points);
                var x = 100;
                setInterval(function(){
                    vm.lineGraphData[0].values.push({ x: x,	y: res.data.points[x].speedkmh});
                  if (vm.lineGraphData[0].values.length > 100) vm.lineGraphData[0].values.shift();
                    x++;

                  $scope.$apply(); // update both chart
                }, 500);
            });


	        /*Random Data Generator */
	        function createDataPoints(points) {
	            var sin = [],sin2 = [],
	                cos = [];
                var carData = [];


	            //Data is represented as an array of {x,y} pairs.
	            for (var i = 0; i < 100; i++) {
	                carData.push({x: i , y: points[i].speedkmh});
//
//	                sin.push({x: i, y: Math.sin(i/10)});
//	                sin2.push({x: i, y: i % 10 == 5 ? null : Math.sin(i/10) *0.25 + 0.5});
//	                cos.push({x: i, y: .5 * Math.cos(i/10+ 2) + Math.random() / 10});
	            }



	            //Line chart data should be sent as an array of series objects.
	            return [
	                {
	                    values: carData,
	                    key: 'Car velocity',
	                    color: 'orange',
	                    area: true      //area - set to true if you want this line to turn into a filled area chart.
	                }
	            ];
	        };

			// End of controller
		}
})();