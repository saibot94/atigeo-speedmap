(function(){
            'use strict';

            angular.module('SrcApp')
                .controller('SearchController', SearchController);

            SearchController.$inject = ['$scope', 'ApiSearchService']

            function SearchController($scope, ApiSearchService){
                var vm = this;

                vm.results = null;
                vm.search = function() {
                    console.log('searching');
                }


                ApiSearchService.GetCoordinates('Timisoara').then(function(res){
                    var responseData = res.data;
                    if(res.data.results.status == 'OK') {
                        vm.results = responseData[0];
                    }

                });

            }


})();