(function(){
		'use strict';

		angular.module('SrcApp')
			.controller('SidebarController', SidebarController);

        SidebarController.$inject = ['$scope', '$location'];
		function SidebarController($scope, $location){
            var vm = this;

            vm.bar = {
                collapsed: false
            };

            vm.getActive = function(url) {
                if(url == $location.url()) {
                    return 'active';
                }
            }

		}

})();