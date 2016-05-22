(function(){
    angular.module('SrcApp')
        .controller('DangerZonesController', DangerZonesController);

    DangerZonesController.$inject = ['ApiAnalyticsService']
    function DangerZonesController(ApiAnalyticsService){
        var vm = this;

        function onlyUnique(value, index, self) {
            return self.indexOf(value) === index;
        }

        ApiAnalyticsService.GetDangerZones().then(function (res){
            vm.dangerousZones = res.data.dangerous.filter( onlyUnique );
            });
    }

})();