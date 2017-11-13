﻿'use strict';
app.controller('espDeviceManagerController', ['$scope', '$timeout', '$log', 'uiGridConstants', 'EventDispatcher', 'espDeviceService', function ($scope, $timeout, $log, uiGridConstants, EventDispatcher, espDeviceService) {    
        
    var onDeleteFromApplicationClick = function (espDevice) {
        espDeviceService.deleteFromApplication(espDevice.hardwareInApplicationId);
    }

    var onDeleteFromApplicationCompleted = function () {
        alert("ESP Device deletado!!!");
    }

    EventDispatcher.on('espDeviceService_onDeleteFromApplicationCompleted', onDeleteFromApplicationCompleted);

    $scope.gridOptions = {                                                 
        enableFiltering: true,
        enableSorting: true,
        showFooter: true,
        rowHeight: 36,
        data: [],
        columnDefs: [
            { name: 'HardwareInApplicationId', field: 'hardwareInApplicationId', width: 270 },
            { name: 'HardwareId', field: 'hardwareId', width: 270 },
            { name: 'ChipId', field: 'chipId', width: 270 },
            { name: 'FlashChipId', field: 'flashChipId', width: 270 },
            { name: 'MacAddress', field: 'macAddress', width: 270 },
            { name: 'Data criação', field: 'createDate', width: 150 },
            { name: 'Ações', cellTemplate: '<div class="text-center"><a ng-click="grid.appScope.deleteFromApplicationClick(row.entity)" class="btn btn-danger" href="" aria-label="Delete"><i class="fa fa-trash-o" aria-hidden="true"></i></a></div>', width: 85 },
        ],
    };

    $scope.deleteFromApplicationClick = onDeleteFromApplicationClick;

    $scope.gridOptions.data = espDeviceService.devices;

}]);