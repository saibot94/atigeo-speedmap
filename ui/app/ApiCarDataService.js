(function(){

        'use strict';

        angular.module('SrcApp')
            .factory('ApiCarDataService', ApiCarDataService);


        ApiCarDataService.$inject = ['$q', '$http', 'LocationService'];
        function ApiCarDataService($q, $http, LocationService) {
            var baseUrl = 'http://52.53.188.254:8080';
            var service = {
                GetPoints: getPoints,
                InitRealtimePoints: initRealtimePoints,
                PollRealtime: pollRealtime
            };


            return service;

            function getPoints(){
                        var defaultDb = LocationService.GetDefaultDb();
``
                if(!defaultDb ){
                    return $http({
                    method: 'GET',
                    url: baseUrl + '/points'
                    });
                }else{
                return $http({
                  method: 'GET',
                  url: baseUrl + '/points',
                  params: {'collection': defaultDb }
                });
               }
            }

             function initRealtimePoints(){
                         var defaultDb = LocationService.GetDefaultDb();
                console.log(defaultDb);
              if(!defaultDb ){

                return $http({
                    method: 'GET',
                    url: baseUrl + '/realtime-points'
                });
                }
                else{

                return $http({
                    method: 'GET',
                    params: {'collection': defaultDb},
                    url: baseUrl + '/realtime-points'
                });
                }
            }


            function pollRealtime(){
                        var defaultDb = LocationService.GetDefaultDb();
                console.log(defaultDb);

                if(!defaultDb ){

                    return $http({
                        method: 'GET',
                        params: {'start_ts' : Date.now()},
                        url: baseUrl + '/realtime-points'
                    });
                }
                else{

                return $http({
                    method: 'GET',
                    params: {'start_ts' : Date.now(), 'collection': defaultDb},
                    url: baseUrl + '/realtime-points'
                });
                }

            }

        }


})();