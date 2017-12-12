﻿namespace ART.Domotica.Repository.Configurations
{
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Infrastructure.Annotations;
    using System.Data.Entity.ModelConfiguration;

    using ART.Domotica.Repository.Entities;

    public class SensorInDeviceConfiguration : EntityTypeConfiguration<SensorInDevice>
    {
        #region Constructors

        public SensorInDeviceConfiguration()
        {
            //Primary Keys
            HasKey(x => new
            {
                x.DeviceSensorsId,
                x.SensorId,
                x.SensorDatasheetId,
                x.SensorTypeId,
            });

            //DeviceId
            Property(x => x.DeviceSensorsId)
                .HasColumnOrder(0)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None)
                .IsRequired();

            //SensorId
            Property(x => x.SensorId)
                .HasColumnOrder(1)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute ("IX_Unique_SensorInDevice", 0) { IsUnique = true }));

            //SensorDatasheetId
            Property(x => x.SensorDatasheetId)
                .HasColumnOrder(2)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute("IX_Unique_SensorInDevice", 1) { IsUnique = true }));

            //SensorTypeId
            Property(x => x.SensorTypeId)
                .HasColumnOrder(3)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute("IX_Unique_SensorInDevice", 2) { IsUnique = true }));

            //DeviceSensors
            HasRequired(x => x.DeviceSensors)
                .WithMany(x => x.SensorInDevice)
                .HasForeignKey(x => x.DeviceSensorsId)
                .WillCascadeOnDelete(false);

            //Sensor
            HasRequired(x => x.Sensor)
                .WithMany(x => x.SensorInDevice)
                .HasForeignKey(x => new
                {
                    x.SensorId,
                    x.SensorDatasheetId,
                    x.SensorTypeId,
                })
                .WillCascadeOnDelete(false);

            //Ordination
            Property(x => x.Ordination)
                .HasColumnOrder(4)
                .IsRequired();
        }

        #endregion Constructors
    }
}