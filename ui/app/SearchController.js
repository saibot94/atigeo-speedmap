(function(){
            'use strict';

            angular.module('SrcApp')
                .controller('SearchController', SearchController);

            SearchController.$inject = ['$scope', 'ApiSearchService', 'LocationService', '$location'];

            function SearchController($scope, ApiSearchService, LocationService, $location){
                var vm = this;
                vm.realtime = false;
                vm.results = null;
                vm.radioData = [
                  { label: 'Historical', value: false },
                  { label: 'Realtime', value: true}
                ];
            vm.search = function(data) {
                console.log(data)
                if(data){
                    ApiSearchService.GetCoordinates(data).then(function(res){
                        console.log(res);
                        if(res.data.status == 'OK') {
                            LocationService.SetLocation(res.data.results[0].formatted_address);
                            LocationService.SetRealtime(vm.realtime);
                            console.log('set realtime to: ' + vm.realtime);
                            $location.path('/dashboard');
                        }
                    });
                }
                }
            }


})();