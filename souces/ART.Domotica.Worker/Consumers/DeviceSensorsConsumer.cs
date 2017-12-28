﻿namespace ART.Domotica.Worker.Consumers
{
    using ART.Domotica.Constant;
    using ART.Domotica.Worker.IConsumers;
    using ART.Infra.CrossCutting.Logging;
    using ART.Infra.CrossCutting.MQ.Worker;

    using Autofac;

    using RabbitMQ.Client;
    using RabbitMQ.Client.Events;
    using System.Threading.Tasks;
    using ART.Infra.CrossCutting.Utils;
    using ART.Infra.CrossCutting.MQ.Contract;
    using ART.Domotica.Domain.Interfaces;
    using global::AutoMapper;
    using ART.Domotica.Repository.Entities;
    using ART.Domotica.Model;
    using ART.Domotica.Contract;
    using ART.Infra.CrossCutting.MQ;

    public class DeviceSensorsConsumer : ConsumerBase, IDeviceSensorsConsumer
    {
        #region Fields
        
        private readonly EventingBasicConsumer _setPublishIntervalInSecondsConsumer;

        #endregion Fields

        #region Constructors

        public DeviceSensorsConsumer(IConnection connection, ILogger logger, IComponentContext componentContext, IMQSettings mqSettings)
            : base(connection, mqSettings, logger, componentContext)
        {            
            _setPublishIntervalInSecondsConsumer = new EventingBasicConsumer(_model);

            Initialize();
        }

        #endregion Constructors

        #region Methods

        private void Initialize()
        {
            BasicQueueDeclare(DeviceSensorsConstants.SetPublishIntervalInSecondsQueueName);

            _setPublishIntervalInSecondsConsumer.Received += SetPublishIntervalInSecondsReceived;

            _model.BasicConsume(DeviceSensorsConstants.SetPublishIntervalInSecondsQueueName, false, _setPublishIntervalInSecondsConsumer);
        }

        private void SetPublishIntervalInSecondsReceived(object sender, BasicDeliverEventArgs e)
        {
            Task.WaitAll(SetPublishIntervalInSecondsReceivedAsync(sender, e));
        }

        public async Task SetPublishIntervalInSecondsReceivedAsync(object sender, BasicDeliverEventArgs e)
        {
            _logger.DebugEnter();

            _model.BasicAck(e.DeliveryTag, false);
            var message = SerializationHelpers.DeserializeJsonBufferToType<AuthenticatedMessageContract<DeviceSensorsSetPublishIntervalInSecondsRequestContract>>(e.Body);
            var deviceSensorsDomain = _componentContext.Resolve<IDeviceSensorsDomain>();
            var data = await deviceSensorsDomain.SetPublishIntervalInSeconds(message.Contract.DeviceSensorsId, message.Contract.DeviceDatasheetId, message.Contract.PublishIntervalInSeconds);

            var applicationMQDomain = _componentContext.Resolve<IApplicationMQDomain>();
            var applicationMQ = await applicationMQDomain.GetByApplicationUserId(message);

            //Enviando para View
            var viewModel = Mapper.Map<DeviceSensors, DeviceSensorsSetPublishIntervalInSecondsModel>(data);
            var viewBuffer = SerializationHelpers.SerializeToJsonBufferAsync(viewModel, true);
            var rountingKey = GetInApplicationRoutingKeyForAllView(applicationMQ.Topic, DeviceSensorsConstants.SetPublishIntervalInSecondsViewCompletedQueueName);
            _model.BasicPublish(defaultExchangeTopic, rountingKey, null, viewBuffer);

            _logger.DebugLeave();
        }

        #endregion Methods
    }
}