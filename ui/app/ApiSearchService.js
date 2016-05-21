(function(){
           'use strict';

            angular.module('SrcApp')
                .factory('ApiSearchService', ApiSearchService);

        	ApiSearchService.$inject = ['$q', '$http'];

            function ApiSearchService ($q, $http) {

                var baseURL = 'https://maps.googleapis.com/maps/api/geocode/json?address=';
                var apiKey = '&key=AIzaSyBAGWk4cH9OQt1KScJPNMsn72ThtBCgdHo';


                var service = {
                    GetCoordinates: getCoordinates
                };



                return service;




            function getCoordinates(cityName){
                if (cityName) {
                    return $http({
                        method: 'GET',
                        url: baseURL + cityName + apiKey
                    });
                }

                }
            }
})();