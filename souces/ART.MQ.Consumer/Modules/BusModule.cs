﻿using ART.MQ.Common.QueueNames;
using ART.MQ.Consumer.Consumers.DSFamilyTempSensorConsumers;
using Autofac;
using MassTransit;
using System.Configuration;

namespace ART.MQ.Consumer.Modules
{
    public class BusModule : Module
    {
        protected override void Load(ContainerBuilder builder)
        {
            builder.Register(context =>
            {
                var busControl = Bus.Factory.CreateUsingRabbitMq(rabbit =>
                {
                    var hostName = ConfigurationManager.AppSettings["RabbitMQHostName"];
                    var virtualHostName = ConfigurationManager.AppSettings["RabbitMQVirtualHostName"];
                    var username = ConfigurationManager.AppSettings["RabbitMQUsername"];
                    var password = ConfigurationManager.AppSettings["RabbitMQPassword"];

                    var host = rabbit.Host(hostName, virtualHostName, settings =>
                    {
                        settings.Username(username);
                        settings.Password(password);
                    });

                    rabbit.ReceiveEndpoint(host, DSFamilyTempSensorQueueNames.DSFamilyTempSensorSetResolutionQueue, e =>
                    {
                        e.Consumer<DSFamilyTempSensorSetResolutionConsumer>(context);
                    });

                });

                return busControl;
            })
                .SingleInstance()
                .As<IBusControl>()
                .As<IBus>();
        }
    }
}