(function(){

        'use strict';

        angular.module('SrcApp')
            .factory('ApiCarDataService', ApiCarDataService);


        ApiCarDataService.$inject = ['$q', '$http'];
        function ApiCarDataService($q, $http) {
            var baseUrl = 'http://52.53.195.124:8080';

            var service = {
                GetPoints: getPoints
            };


            return service;

            function getPoints(){
                return $http({
                  method: 'GET',
                  url: baseUrl + '/points',
                });
            }

        }


})();