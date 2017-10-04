﻿namespace ART.Seguranca.Repository.Configurations
{
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Infrastructure.Annotations;
    using System.Data.Entity.ModelConfiguration;

    using ART.Seguranca.Repository.Entities;

    public class ApplicationUserConfiguration : EntityTypeConfiguration<ApplicationUser>
    {
        #region Constructors

        public ApplicationUserConfiguration()
        {
            //Primary Keys
            HasKey(x => x.Id);

            //Id
            Property(x => x.Id)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.Identity)
                .IsRequired();            
        }

        #endregion Constructors
    }
}