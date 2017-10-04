﻿using Microsoft.AspNet.Identity.EntityFramework;
using System;
using System.Collections.Generic;

namespace ART.Seguranca.DistributedServices.Entities
{
    public class ApplicationUser : IdentityUser<Guid, ApplicationUserLogin, ApplicationUserRole, ApplicationUserClaim>
    {
        #region Primitive Properties


        #endregion

        #region Navigation Properties

        public ICollection<UsersInApplication> UsersInApplication { get; set; }

        #endregion
    }
}