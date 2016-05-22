(function(){


    'use strict';

    angular.module('SrcApp')
        .factory('ApiAnalyticsService', ApiAnalyticsService);



    ApiAnalyticsService.$inject = ['$http'];
    function ApiAnalyticsService($http){
        var baseUrl = 'http://52.53.195.124:8080'
        var service = {
            GetSpeedStats: getSpeedStats,
            GetDangerZones: getDangerZones,
            GetIllegalitiesCount: getIllegalitiesCount
        };

        return service;



        function getSpeedStats(){
            return $http({
                method: 'GET',
                url: baseUrl + '/stats/speed'

            });
        }

        function getDangerZones(){
            return $http({
                method: 'GET',
                url: baseUrl + '/stats/dangerous-streets'
            });
        }


        function getIllegalitiesCount(){
            return $http({
                method: 'GET',
                url: baseUrl + '/stats/illegalities-count'
            });
        }


    }
})();