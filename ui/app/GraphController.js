(function () {
	'use strict';

		angular.module('SrcApp')
			.controller('GraphController', GraphController);

		GraphController.$inject = ['$scope'];

		function GraphController($scope) {
			var vm = this;

			vm.lineGraphOptions = {
				chart: {
					type: 'lineChart', 
					height: 450,
					margin :{ 
						top: 30,
						bottom: 30,
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
	                    axisLabel: 'Voltage (v)',
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
                	text: 'Some analytics shit here'
            	},
            	subtitle: {
                	enable: true,
                	text: 'Subtitle for simple line chart. Lorem ipsum dolor sit amet, at eam blandit sadipscing, vim adhuc sanctus disputando ex, cu usu affert alienum urbanitas.',
                	css: {
	                    'text-align': 'center',
     	               'margin': '10px 13px 0px 7px'
        	        }
            	}

			};
		
			vm.lineGraphData = sinAndCos();

	        /*Random Data Generator */
	        function sinAndCos() {
	            var sin = [],sin2 = [],
	                cos = [];

	            //Data is represented as an array of {x,y} pairs.
	            for (var i = 0; i < 100; i++) {
	                sin.push({x: i, y: Math.sin(i/10)});
	                sin2.push({x: i, y: i % 10 == 5 ? null : Math.sin(i/10) *0.25 + 0.5});
	                cos.push({x: i, y: .5 * Math.cos(i/10+ 2) + Math.random() / 10});
	            }

	            //Line chart data should be sent as an array of series objects.
	            return [
	                {
	                    values: sin,      //values - represents the array of {x,y} data points
	                    key: 'Sine Wave', //key  - the name of the series.
	                    color: '#ff7f0e'  //color - optional: choose your own line color.
	                },
	                {
	                    values: cos,
	                    key: 'Cosine Wave',
	                    color: '#2ca02c'
	                },
	                {
	                    values: sin2,
	                    key: 'Another sine wave',
	                    color: '#7777ff',
	                    area: true      //area - set to true if you want this line to turn into a filled area chart.
	                }
	            ];
	        };

			// End of controller
		}
})();