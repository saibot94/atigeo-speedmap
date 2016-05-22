(function(){

        'use strict';

        angular.module('SrcApp')
            .factory('ApiCarDataService', ApiCarDataService);


        ApiCarDataService.$inject = ['$q', '$http'];
        function ApiCarDataService($q, $http) {
            var baseUrl = 'http://52.53.195.124:8080';

            var service = {
                GetPoints: getPoints,
                InitRealtimePoints: initRealtimePoints,
                PollRealtime: pollRealtime
            };


            return service;

            function getPoints(){
                return $http({
                  method: 'GET',
                  url: baseUrl + '/points',
                });
            }

            function initRealtimePoints(){
                return $http({
                    method: 'GET',
                    params: {'realtime': true},
                    url: baseUrl + '/points'
                });
            }


            function pollRealtime(){
                return $http({
                    method: 'GET',
                    params: {'start_ts' : Date.now()},
                    url: baseUrl + '/points'
                });
            }

        }


})();