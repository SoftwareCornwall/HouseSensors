CREATE DATABASE  IF NOT EXISTS `sensor_data` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `sensor_data`;
-- MySQL dump 10.13  Distrib 5.5.55, for debian-linux-gnu (armv7l)
--
-- Host: 127.0.0.1    Database: sensor_data
-- ------------------------------------------------------
-- Server version	5.5.55-0+deb8u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `humidity`
--

DROP TABLE IF EXISTS `humidity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `humidity` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `humidity_value` varchar(45) DEFAULT NULL,
  `humidity_timestamp` varchar(100) DEFAULT NULL,
  `mac_address` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=941 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `humidity`
--

LOCK TABLES `humidity` WRITE;
/*!40000 ALTER TABLE `humidity` DISABLE KEYS */;
INSERT INTO `humidity` VALUES (637,'33.127850','1500899100','b8:27:eb:c6:75:f5'),(638,'33.240070','1500902100','b8:27:eb:c6:75:f5'),(639,'45.904209','1500909300','b8:27:eb:89:9c:2d'),(640,'39.951096','1500909600','b8:27:eb:89:9c:2d'),(641,'37.963455','1500909900','b8:27:eb:89:9c:2d'),(642,'36.790630','1500909900','b8:27:eb:c6:75:f5'),(643,'35.306816','1500910200','b8:27:eb:c6:75:f5'),(644,'36.619839','1500910200','b8:27:eb:89:9c:2d'),(645,'34.418396','1500910500','b8:27:eb:c6:75:f5'),(646,'35.773132','1500910500','b8:27:eb:89:9c:2d'),(647,'34.109787','1500910800','b8:27:eb:c6:75:f5'),(648,'35.259872','1500910800','b8:27:eb:89:9c:2d'),(649,'34.044323','1500911100','b8:27:eb:c6:75:f5'),(650,'35.161800','1500911100','b8:27:eb:89:9c:2d'),(651,'35.034302','1500911400','b8:27:eb:89:9c:2d'),(652,'33.611023','1500911400','b8:27:eb:c6:75:f5'),(653,'34.841423','1500911700','b8:27:eb:89:9c:2d'),(654,'33.514389','1500911700','b8:27:eb:c6:75:f5'),(655,'33.701424','1500912000','b8:27:eb:c6:75:f5'),(656,'35.135647','1500912000','b8:27:eb:89:9c:2d'),(657,'45.629601','1500969900','b8:27:eb:89:9c:2d'),(658,'44.128662','1500969900','b8:27:eb:c6:75:f5'),(659,'41.598747','1500970200','b8:27:eb:89:9c:2d'),(660,'40.615509','1500970200','b8:27:eb:c6:75:f5'),(661,'37.794388','1500970500','b8:27:eb:c6:75:f5'),(662,'39.222076','1500970500','b8:27:eb:89:9c:2d'),(663,'36.572422','1500970800','b8:27:eb:c6:75:f5'),(664,'38.728436','1500970800','b8:27:eb:89:9c:2d'),(665,'36.672146','1500971100','b8:27:eb:89:9c:2d'),(666,'37.102356','1500971100','b8:27:eb:c6:75:f5'),(667,'36.103313','1500971400','b8:27:eb:89:9c:2d'),(668,'35.026260','1500971400','b8:27:eb:c6:75:f5'),(669,'36.155621','1500971700','b8:27:eb:89:9c:2d'),(670,'34.677128','1500971700','b8:27:eb:c6:75:f5'),(671,'34.883923','1500972000','b8:27:eb:89:9c:2d'),(672,'33.953922','1500972000','b8:27:eb:c6:75:f5'),(673,'35.024498','1500972300','b8:27:eb:89:9c:2d'),(674,'32.532452','1500972300','b8:27:eb:c6:75:f5'),(675,'34.628929','1500972600','b8:27:eb:89:9c:2d'),(676,'32.261250','1500972600','b8:27:eb:c6:75:f5'),(677,'34.890461','1500972900','b8:27:eb:89:9c:2d'),(678,'34.373936','1500973200','b8:27:eb:89:9c:2d'),(679,'32.816124','1500973200','b8:27:eb:c6:75:f5'),(680,'34.187595','1500973500','b8:27:eb:89:9c:2d'),(681,'32.463875','1500973500','b8:27:eb:c6:75:f5'),(682,'31.821718','1500973800','b8:27:eb:c6:75:f5'),(683,'33.648186','1500973800','b8:27:eb:89:9c:2d'),(684,'33.628571','1500974100','b8:27:eb:89:9c:2d'),(685,'31.441412','1500974100','b8:27:eb:c6:75:f5'),(686,'33.792030','1500974400','b8:27:eb:89:9c:2d'),(687,'32.083569','1500974400','b8:27:eb:c6:75:f5'),(688,'33.465115','1500974700','b8:27:eb:89:9c:2d'),(689,'31.612862','1500974700','b8:27:eb:c6:75:f5'),(690,'31.391535','1500975000','b8:27:eb:c6:75:f5'),(691,'33.347424','1500975000','b8:27:eb:89:9c:2d'),(692,'31.235672','1500975300','b8:27:eb:c6:75:f5'),(693,'33.213390','1500975300','b8:27:eb:89:9c:2d'),(694,'33.219929','1500975600','b8:27:eb:89:9c:2d'),(695,'30.952002','1500975600','b8:27:eb:c6:75:f5'),(696,'32.886475','1500975900','b8:27:eb:89:9c:2d'),(697,'30.880304','1500975900','b8:27:eb:c6:75:f5'),(698,'30.961353','1500976200','b8:27:eb:c6:75:f5'),(699,'32.955128','1500976200','b8:27:eb:89:9c:2d'),(700,'33.723377','1500976500','b8:27:eb:89:9c:2d'),(701,'30.945766','1500976500','b8:27:eb:c6:75:f5'),(702,'33.278774','1500976800','b8:27:eb:89:9c:2d'),(703,'31.372831','1500976800','b8:27:eb:c6:75:f5'),(704,'31.061106','1500977100','b8:27:eb:c6:75:f5'),(705,'34.246441','1500977100','b8:27:eb:89:9c:2d'),(706,'32.562832','1500977400','b8:27:eb:89:9c:2d'),(707,'30.733793','1500977400','b8:27:eb:c6:75:f5'),(708,'33.291851','1500977700','b8:27:eb:89:9c:2d'),(709,'30.852249','1500977700','b8:27:eb:c6:75:f5'),(710,'33.275505','1500978000','b8:27:eb:89:9c:2d'),(711,'30.814842','1500978000','b8:27:eb:c6:75:f5'),(712,'30.693270','1500978300','b8:27:eb:c6:75:f5'),(713,'33.429153','1500978300','b8:27:eb:89:9c:2d'),(714,'32.889744','1500978600','b8:27:eb:89:9c:2d'),(715,'30.574814','1500978600','b8:27:eb:c6:75:f5'),(716,'30.917711','1500978900','b8:27:eb:c6:75:f5'),(717,'32.248993','1500978900','b8:27:eb:89:9c:2d'),(718,'31.014347','1500979200','b8:27:eb:c6:75:f5'),(719,'32.294762','1500979200','b8:27:eb:89:9c:2d'),(720,'31.346708','1500979500','b8:27:eb:89:9c:2d'),(721,'30.989408','1500979500','b8:27:eb:c6:75:f5'),(722,'29.620932','1500979800','b8:27:eb:c6:75:f5'),(723,'33.004166','1500979800','b8:27:eb:89:9c:2d'),(724,'32.036808','1500980100','b8:27:eb:c6:75:f5'),(725,'32.651096','1500980100','b8:27:eb:89:9c:2d'),(726,'31.612862','1500980400','b8:27:eb:c6:75:f5'),(727,'32.742634','1500980400','b8:27:eb:89:9c:2d'),(728,'32.928974','1500980700','b8:27:eb:89:9c:2d'),(729,'32.120975','1500980700','b8:27:eb:c6:75:f5'),(730,'31.467667','1500981000','b8:27:eb:89:9c:2d'),(731,'31.322956','1500981000','b8:27:eb:c6:75:f5'),(732,'30.821077','1500981300','b8:27:eb:c6:75:f5'),(733,'32.461487','1500981300','b8:27:eb:89:9c:2d'),(734,'32.350334','1500981600','b8:27:eb:89:9c:2d'),(735,'31.089161','1500981600','b8:27:eb:c6:75:f5'),(736,'30.958237','1500981900','b8:27:eb:c6:75:f5'),(737,'30.895891','1500982200','b8:27:eb:c6:75:f5'),(738,'31.609743','1500982500','b8:27:eb:c6:75:f5'),(739,'30.867836','1500982800','b8:27:eb:c6:75:f5'),(740,'30.917711','1500983100','b8:27:eb:c6:75:f5'),(741,'34.805462','1500983240',''),(742,'36.211197','1500983250',''),(743,'34.596237','1500983310',''),(744,'30.842897','1500983400','b8:27:eb:c6:75:f5'),(745,'30.793022','1500983700','b8:27:eb:c6:75:f5'),(746,'31.145271','1500984000','b8:27:eb:c6:75:f5'),(747,'31.319839','1500984300','b8:27:eb:c6:75:f5'),(748,'31.335424','1500984600','b8:27:eb:c6:75:f5'),(749,'31.276197','1500984900','b8:27:eb:c6:75:f5'),(750,'31.135920','1500985200','b8:27:eb:c6:75:f5'),(751,'31.491287','1500985500','b8:27:eb:c6:75:f5'),(752,'31.291782','1500985800','b8:27:eb:c6:75:f5'),(753,'36.263504','1500985800','b8:27:eb:0b:04:1a'),(754,'36.404076','1500985810','b8:27:eb:0b:04:1a'),(755,'36.175236','1500985820','b8:27:eb:0b:04:1a'),(756,'36.217735','1500985830','b8:27:eb:0b:04:1a'),(757,'36.276577','1500985840','b8:27:eb:0b:04:1a'),(758,'35.586788','1500985850','b8:27:eb:0b:04:1a'),(759,'35.711018','1500985940','b8:27:eb:0b:04:1a'),(760,'35.907166','1500985950','b8:27:eb:0b:04:1a'),(761,'31.463232','1500986100','b8:27:eb:c6:75:f5'),(762,'31.884062','1500986400','b8:27:eb:c6:75:f5'),(763,'34.684505','1500986430','b8:27:eb:0b:04:1a'),(764,'34.756428','1500986440','b8:27:eb:0b:04:1a'),(765,'34.998344','1500986450','b8:27:eb:0b:04:1a'),(766,'34.736813','1500986460','b8:27:eb:0b:04:1a'),(767,'34.910076','1500986470','b8:27:eb:0b:04:1a'),(768,'34.818539','1500986480','b8:27:eb:0b:04:1a'),(769,'34.975460','1500986490','b8:27:eb:0b:04:1a'),(770,'34.151634','1500986500','b8:27:eb:0b:04:1a'),(771,'35.619480','1500986510','b8:27:eb:0b:04:1a'),(772,'35.233723','1500986520','b8:27:eb:0b:04:1a'),(773,'34.599506','1500986530','b8:27:eb:0b:04:1a'),(774,'34.851231','1500986540','b8:27:eb:0b:04:1a'),(775,'34.952576','1500986550','b8:27:eb:0b:04:1a'),(776,'35.357948','1500986560','b8:27:eb:0b:04:1a'),(777,'35.580250','1500986570','b8:27:eb:0b:04:1a'),(778,'34.243172','1500986580','b8:27:eb:0b:04:1a'),(779,'34.681236','1500986590','b8:27:eb:0b:04:1a'),(780,'34.619122','1500986600','b8:27:eb:0b:04:1a'),(781,'34.841423','1500986610','b8:27:eb:0b:04:1a'),(782,'33.589340','1500986620','b8:27:eb:0b:04:1a'),(783,'35.884281','1500986630','b8:27:eb:0b:04:1a'),(784,'34.298744','1500986640','b8:27:eb:0b:04:1a'),(785,'34.014332','1500986650','b8:27:eb:0b:04:1a'),(786,'33.984909','1500986660','b8:27:eb:0b:04:1a'),(787,'34.409897','1500986670','b8:27:eb:0b:04:1a'),(788,'33.151276','1500986680','b8:27:eb:0b:04:1a'),(789,'34.331436','1500986690','b8:27:eb:0b:04:1a'),(790,'34.740082','1500986700','b8:27:eb:0b:04:1a'),(791,'32.367237','1500986700','b8:27:eb:c6:75:f5'),(792,'34.583160','1500986710','b8:27:eb:0b:04:1a'),(793,'34.082981','1500986720','b8:27:eb:0b:04:1a'),(794,'34.030678','1500986730','b8:27:eb:0b:04:1a'),(795,'32.955128','1500986740','b8:27:eb:0b:04:1a'),(796,'34.998344','1500986750','b8:27:eb:0b:04:1a'),(797,'34.305283','1500986760','b8:27:eb:0b:04:1a'),(798,'33.906448','1500986770','b8:27:eb:0b:04:1a'),(799,'33.945679','1500986780','b8:27:eb:0b:04:1a'),(800,'33.935871','1500986790','b8:27:eb:0b:04:1a'),(801,'33.376846','1500986800','b8:27:eb:0b:04:1a'),(802,'33.625301','1500986810','b8:27:eb:0b:04:1a'),(803,'33.916256','1500986820','b8:27:eb:0b:04:1a'),(804,'33.703762','1500986830','b8:27:eb:0b:04:1a'),(805,'33.386654','1500986840','b8:27:eb:0b:04:1a'),(806,'33.631840','1500986850','b8:27:eb:0b:04:1a'),(807,'32.326714','1500987300','b8:27:eb:c6:75:f5'),(808,'32.323597','1500987600','b8:27:eb:c6:75:f5'),(809,'32.223843','1500987900','b8:27:eb:c6:75:f5'),(810,'31.946407','1500988200','b8:27:eb:c6:75:f5'),(811,'32.180202','1500988500','b8:27:eb:c6:75:f5'),(812,'31.450764','1500988800','b8:27:eb:c6:75:f5'),(813,'31.905884','1500989100','b8:27:eb:c6:75:f5'),(814,'32.756897','1500989400','b8:27:eb:c6:75:f5'),(815,'32.279953','1500989700','b8:27:eb:c6:75:f5'),(816,'31.940174','1500990000','b8:27:eb:c6:75:f5'),(817,'32.373474','1500990300','b8:27:eb:c6:75:f5'),(818,'31.880945','1500990600','b8:27:eb:c6:75:f5'),(819,'31.170210','1500990900','b8:27:eb:c6:75:f5'),(820,'30.961353','1500991200','b8:27:eb:c6:75:f5'),(821,'30.783670','1500991500','b8:27:eb:c6:75:f5'),(822,'30.640276','1500991800','b8:27:eb:c6:75:f5'),(823,'30.462591','1500992100','b8:27:eb:c6:75:f5'),(824,'30.668331','1500992400','b8:27:eb:c6:75:f5'),(825,'30.973824','1500992700','b8:27:eb:c6:75:f5'),(826,'31.884062','1500993000','b8:27:eb:c6:75:f5'),(827,'32.027458','1500993300','b8:27:eb:c6:75:f5'),(828,'32.389057','1500993600','b8:27:eb:c6:75:f5'),(829,'47.643394','1500993890','b8:27:eb:0b:04:1a'),(830,'32.619736','1500993900','b8:27:eb:c6:75:f5'),(831,'46.786880','1500993900','b8:27:eb:0b:04:1a'),(832,'46.754189','1500993910','b8:27:eb:0b:04:1a'),(833,'32.837944','1500994200','b8:27:eb:c6:75:f5'),(834,'37.796730','1500994390','b8:27:eb:0b:04:1a'),(835,'31.428942','1500994500','b8:27:eb:c6:75:f5'),(836,'37.188671','1500994550','b8:27:eb:0b:04:1a'),(837,'37.172325','1500994570','b8:27:eb:0b:04:1a'),(838,'37.015404','1500994580','b8:27:eb:0b:04:1a'),(839,'37.084057','1500994590','b8:27:eb:0b:04:1a'),(840,'37.110210','1500994600','b8:27:eb:0b:04:1a'),(841,'36.838871','1500994610','b8:27:eb:0b:04:1a'),(842,'36.054276','1500994620','b8:27:eb:0b:04:1a'),(843,'36.910793','1500994630','b8:27:eb:0b:04:1a'),(844,'36.815987','1500994640','b8:27:eb:0b:04:1a'),(845,'32.803654','1500994800','b8:27:eb:c6:75:f5'),(846,'32.809891','1500995100','b8:27:eb:c6:75:f5'),(847,'32.825474','1500995400','b8:27:eb:c6:75:f5'),(848,'32.625969','1500995700','b8:27:eb:c6:75:f5'),(849,'32.869118','1500996000','b8:27:eb:c6:75:f5'),(850,'32.342300','1500996300','b8:27:eb:c6:75:f5'),(851,'36.541378','1500996320','b8:27:eb:0b:04:1a'),(852,'32.027458','1500996600','b8:27:eb:c6:75:f5'),(853,'31.827951','1500996900','b8:27:eb:c6:75:f5'),(854,'31.993166','1500997200','b8:27:eb:c6:75:f5'),(855,'31.884062','1500997500','b8:27:eb:c6:75:f5'),(856,'31.986933','1500997800','b8:27:eb:c6:75:f5'),(857,'32.024338','1500998100','b8:27:eb:c6:75:f5'),(858,'32.454521','1500998400','b8:27:eb:c6:75:f5'),(859,'31.924587','1500998700','b8:27:eb:c6:75:f5'),(860,'36.924671','1501056300','b8:27:eb:c6:75:f5'),(861,'36.871681','1501056600','b8:27:eb:c6:75:f5'),(862,'76.349754','1501056820','b8:27:eb:0b:04:1a'),(863,'37.024426','1501056900','b8:27:eb:c6:75:f5'),(864,'71.128929','1501056940','b8:27:eb:0b:04:1a'),(865,'70.641830','1501056950','b8:27:eb:0b:04:1a'),(866,'70.236450','1501056960','b8:27:eb:0b:04:1a'),(867,'69.700317','1501056970','b8:27:eb:0b:04:1a'),(868,'36.223289','1501057200','b8:27:eb:c6:75:f5'),(869,'36.662823','1501057500','b8:27:eb:c6:75:f5'),(870,'36.575539','1501057800','b8:27:eb:c6:75:f5'),(871,'36.410324','1501058100','b8:27:eb:c6:75:f5'),(872,'37.089886','1501058400','b8:27:eb:c6:75:f5'),(873,'37.189640','1501058700','b8:27:eb:c6:75:f5'),(874,'37.304977','1501059000','b8:27:eb:c6:75:f5'),(875,'37.230164','1501059300','b8:27:eb:c6:75:f5'),(876,'37.024426','1501059600','b8:27:eb:c6:75:f5'),(877,'37.198990','1501059900','b8:27:eb:c6:75:f5'),(878,'36.949612','1501060200','b8:27:eb:c6:75:f5'),(879,'37.121059','1501060500','b8:27:eb:c6:75:f5'),(880,'37.713341','1501060800','b8:27:eb:c6:75:f5'),(881,'37.320564','1501061100','b8:27:eb:c6:75:f5'),(882,'37.161583','1501061400','b8:27:eb:c6:75:f5'),(883,'37.551243','1501061700','b8:27:eb:c6:75:f5'),(884,'37.442139','1501062000','b8:27:eb:c6:75:f5'),(885,'37.326797','1501062300','b8:27:eb:c6:75:f5'),(886,'37.370441','1501062600','b8:27:eb:c6:75:f5'),(887,'37.301861','1501062900','b8:27:eb:c6:75:f5'),(888,'37.616703','1501063200','b8:27:eb:c6:75:f5'),(889,'37.373558','1501063500','b8:27:eb:c6:75:f5'),(890,'37.622940','1501063800','b8:27:eb:c6:75:f5'),(891,'36.625416','1501064100','b8:27:eb:c6:75:f5'),(892,'37.616703','1501064400','b8:27:eb:c6:75:f5'),(893,'37.632290','1501064700','b8:27:eb:c6:75:f5'),(894,'37.336151','1501065000','b8:27:eb:c6:75:f5'),(895,'37.345505','1501065300','b8:27:eb:c6:75:f5'),(896,'37.632290','1501065600','b8:27:eb:c6:75:f5'),(897,'37.121059','1501065900','b8:27:eb:c6:75:f5'),(898,'37.280041','1501066200','b8:27:eb:c6:75:f5'),(899,'37.205227','1501066500','b8:27:eb:c6:75:f5'),(900,'37.167820','1501066800','b8:27:eb:c6:75:f5'),(901,'37.295628','1501067100','b8:27:eb:c6:75:f5'),(902,'37.139763','1501067400','b8:27:eb:c6:75:f5'),(903,'37.314331','1501067700','b8:27:eb:c6:75:f5'),(904,'36.949612','1501068000','b8:27:eb:c6:75:f5'),(905,'36.862328','1501068300','b8:27:eb:c6:75:f5'),(906,'37.170937','1501068600','b8:27:eb:c6:75:f5'),(907,'36.703346','1501068900','b8:27:eb:c6:75:f5'),(908,'36.631649','1501069200','b8:27:eb:c6:75:f5'),(909,'36.681526','1501069500','b8:27:eb:c6:75:f5'),(910,'37.040012','1501069800','b8:27:eb:c6:75:f5'),(911,'37.809975','1501070100','b8:27:eb:c6:75:f5'),(912,'36.877914','1501070400','b8:27:eb:c6:75:f5'),(913,'36.441498','1501070700','b8:27:eb:c6:75:f5'),(914,'36.354214','1501071000','b8:27:eb:c6:75:f5'),(915,'36.229523','1501071300','b8:27:eb:c6:75:f5'),(916,'36.946495','1501071600','b8:27:eb:c6:75:f5'),(917,'36.136005','1501071900','b8:27:eb:c6:75:f5'),(918,'35.515671','1501072200','b8:27:eb:c6:75:f5'),(919,'35.839867','1501072500','b8:27:eb:c6:75:f5'),(920,'35.677769','1501072800','b8:27:eb:c6:75:f5'),(921,'34.505680','1501073100','b8:27:eb:c6:75:f5'),(922,'35.203945','1501073400','b8:27:eb:c6:75:f5'),(923,'35.303696','1501073700','b8:27:eb:c6:75:f5'),(924,'34.091084','1501074000','b8:27:eb:c6:75:f5'),(925,'35.980141','1501074300','b8:27:eb:c6:75:f5'),(926,'35.054317','1501074600','b8:27:eb:c6:75:f5'),(927,'35.094841','1501074900','b8:27:eb:c6:75:f5'),(928,'34.910923','1501075200','b8:27:eb:c6:75:f5'),(929,'34.140961','1501075500','b8:27:eb:c6:75:f5'),(930,'35.191475','1501075800','b8:27:eb:c6:75:f5'),(931,'33.523743','1501076100','b8:27:eb:c6:75:f5'),(932,'33.118496','1501076400','b8:27:eb:c6:75:f5'),(933,'31.965111','1501076700','b8:27:eb:c6:75:f5'),(934,'32.722607','1501077000','b8:27:eb:c6:75:f5'),(935,'32.064865','1501077300','b8:27:eb:c6:75:f5'),(936,'32.370354','1501077600','b8:27:eb:c6:75:f5'),(937,'31.023699','1501077900','b8:27:eb:c6:75:f5'),(938,'31.562984','1501078200','b8:27:eb:c6:75:f5'),(939,'31.547398','1501078500','b8:27:eb:c6:75:f5'),(940,'31.594158','1501078800','b8:27:eb:c6:75:f5');
/*!40000 ALTER TABLE `humidity` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-07-26 16:35:19
