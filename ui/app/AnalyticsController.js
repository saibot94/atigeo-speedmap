(function() {
    'use strict';


        angular.module('SrcApp')
            .controller('AnalyticsController', AnalyticsController);

		AnalyticsController.$inject = ['$scope', 'ApiAnalyticsService'];
		function AnalyticsController ($scope, ApiAnalyticsService) {
		    var vm = this;

		}

})();