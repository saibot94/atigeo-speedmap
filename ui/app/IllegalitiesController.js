(function(){
        'use strict';


        angular.module('SrcApp')
            .controller('IllegalitiesController', IllegalitiesController);

		IllegalitiesController.$inject = ['$scope', 'ApiAnalyticsService'];
		function IllegalitiesController ($scope, ApiAnalyticsService) {
		    var vm = this;

            ApiAnalyticsService.GetIllegalitiesCount().then(function(res){
                vm.illegalities = res.data.count;
            });

		}


})();