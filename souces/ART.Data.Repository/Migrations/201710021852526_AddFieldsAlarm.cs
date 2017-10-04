namespace ART.Data.Repository.Migrations
{
    using System.Data.Entity.Migrations;

    public partial class AddFieldsAlarm : DbMigration
    {
        #region Methods

        public override void Down()
        {
            DropColumn("dbo.DSFamilyTempSensor", "LowAlarm");
            DropColumn("dbo.DSFamilyTempSensor", "HighAlarm");
        }

        public override void Up()
        {
            AddColumn("dbo.DSFamilyTempSensor", "HighAlarm", c => c.Decimal(nullable: false, precision: 6, scale: 3));
            AddColumn("dbo.DSFamilyTempSensor", "LowAlarm", c => c.Decimal(nullable: false, precision: 6, scale: 3));
        }

        #endregion Methods
    }
}