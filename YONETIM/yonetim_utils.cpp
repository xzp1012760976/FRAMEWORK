#include <QDate>
#include <QCoreApplication>
#include <QSettings>
#include <QDesktopServices>
#include <QUrl>
#include "kernel_utils.h"
#include "adak_sql.h"
#include "adak_defines.h"
#include "yonetim.h"
#include "yonetim_utils.h"
#include "adak_utils.h"
#include "sekme_menu_kernel.h"
#include "hata_istek_batch.h"
#include "yonetim_hakkinda.h"
#include "login.h"

extern ADAK_SQL * G_YONETIM_DB;
extern ADAK_SQL * DB;

static int g_bilgisayarda_calisabilecek_kullanici_sayisi;

extern QList<QWidget *> G_SEKME_MENU_KERNEL;

/**************************************************************************************
                   SET_BILGISAYARDA_KAYITLI_KULLANICI_SAYISI
***************************************************************************************/

void SET_BILGISAYARDA_KAYITLI_KULLANICI_SAYISI ( int p_kullanici_sayisi )
{
    g_bilgisayarda_calisabilecek_kullanici_sayisi = p_kullanici_sayisi;
}

/**************************************************************************************
                   GET_BILGISAYARDA_KAYITLI_KULLANICI_SAYISI
***************************************************************************************/

int GET_BILGISAYARDA_KAYITLI_KULLANICI_SAYISI ()
{
    return g_bilgisayarda_calisabilecek_kullanici_sayisi;
}

/**************************************************************************************
                   KULLANICI_BILGISI_OLUSTUR
***************************************************************************************/

QString KULLANICI_BILGISI_OLUSTUR ( int kullanici_id )
{
    SQL_QUERY sql_query (G_YONETIM_DB);
    sql_query.PREPARE_SELECT ( "ynt_kullanicilar","kullanici_kodu, kullanici_adi","kullanici_id = :kullanici_id");
    sql_query.SET_VALUE      ( ":kullanici_id", kullanici_id );
    if ( sql_query.SELECT() EQ 0 ) {
        return NULL;
    }
    sql_query.NEXT();
    if ( kullanici_id EQ 1 ) {
        return  sql_query.VALUE(0).toString();
    }
    return  sql_query.VALUE(0).toString() + " # " + sql_query.VALUE(1).toString();
}

/**************************************************************************************
                   BILGISAYAR_BILGISI_OLUSTUR
***************************************************************************************/

QString BILGISAYAR_BILGISI_OLUSTUR ( int bilgisayar_id )
{
    SQL_QUERY sql_query ( G_YONETIM_DB );
    sql_query.PREPARE_SELECT ( "ynt_bilgisayarlar","bilgisayar_adi, mac_adresi_kablolu, mac_adresi_kablosuz, mac_adresi_3g, "
                               "dongle_ip","bilgisayar_id = :bilgisayar_id ","");
    sql_query.SET_VALUE      ( ":bilgisayar_id", bilgisayar_id );
    if ( sql_query.SELECT() EQ 0 ) {
        QString     mac_adresi      = "";
        QStringList mac_adressleri  = GET_MAC_ADDRESS();

        for ( int i =0 ; i < mac_adressleri.size() ; i++ ) {
            mac_adresi.append(QString(mac_adressleri.at(0) + "-"));
        }

        return "KAYITLI DEGIL # MAC: " + mac_adresi +" # DONGLE: "+ GET_DONGLE_IP();
    }
    sql_query.NEXT();
    return sql_query.VALUE(0).toString() + " # Kablolu Ağ Mac Adresi" + sql_query.VALUE(1).toString()
            + " # Kablosuz Ağ Mac Adresi " + sql_query.VALUE(2).toString() +
            " # 3G Mac Adresi " + sql_query.VALUE(3).toString() + " # Donge IP " + sql_query.VALUE(4).toString();

}

/**************************************************************************************
                   YONETIM_007_KAYIT
***************************************************************************************/

void YONETIM_007_KAYIT ( int log_turu, int log_islemi, QString log_detaylari )
{
    SQL_QUERY sql_query ( G_YONETIM_DB );
    sql_query.PREPARE_INSERT ( "ynt_007","id","islem_tarihi, islem_saati, kullanici_id,bilgisayar_id, log_turu, log_islemi, log_detaylari" );
    sql_query.SET_VALUE      ( ":islem_tarihi"  , QDate::currentDate().toString("yyyy.MM.dd"));
    sql_query.SET_VALUE      ( ":islem_saati"   , QTime::currentTime().toString("hh:mm"));
    sql_query.SET_VALUE      ( ":kullanici_id"  , KULLANICI_ID() );
    sql_query.SET_VALUE      ( ":bilgisayar_id" , BILGISAYAR_ID() );
    sql_query.SET_VALUE      ( ":log_turu"      , log_turu        );
    sql_query.SET_VALUE      ( ":log_islemi"    , log_islemi      );
    sql_query.SET_VALUE      ( ":log_detaylari" , log_detaylari   );
    sql_query.INSERT();
}

/**************************************************************************************
                   YONETIM_007_CIKIS_KAYDI
***************************************************************************************/

void YONETIM_007_CIKIS_KAYDI ()
{
    G_YONETIM_DB->START_TRANSACTION();

    SQL_QUERY sql_query ( G_YONETIM_DB );

    sql_query.PREPARE_SELECT ( "ynt_veritabanlari","veritabani_ismi, veritabani_tanimi","veritabani_id = :veritabani_id");

    sql_query.SET_VALUE      ( ":veritabani_id",VERITABANI_ID());
    if ( sql_query.SELECT() EQ 0 ) {
        G_YONETIM_DB->CANCEL_TRANSACTION();
        return;
    }
    sql_query.NEXT();
    QString aciklama = "Veritabanı İsmi: " + sql_query.VALUE(0).toString() + " # Veritabanı Tanımı: "+ sql_query.VALUE(1).toString();

    YONETIM_007_KAYIT ( LOG_PROGRAM, LOG_PROGRAMDAN_CIKIS, aciklama );
    G_YONETIM_DB->COMMIT_TRANSACTION ();
}

/**************************************************************************************
                   BILGISAYARDA_KAYITLI_KUL_SAY_VE_KULLANICININ_KAYITLI_VERITABANI_SAY_GUNCELLE
***************************************************************************************/

void BILGISAYARDA_KAYITLI_KUL_SAY_VE_KULLANICININ_KAYITLI_VERITABANI_SAY_GUNCELLE ()
{
    SET_BILGISAYARDA_KAYITLI_KULLANICI_SAYISI         ( BILGISAYARDA_KAYITLI_KULLANICI_SAYISINI_BUL() );
    SET_KULLANICININ_CALISABILECEGI_VERITABANI_SAYISI ( KULLANICININ_CALISABILECEGI_VERITABANI_SAYISINI_BUL() );

}

/**************************************************************************************
                   CHECK_VERSION_UPGRADES
***************************************************************************************/

void CHECK_VERSION_UPGRADES (QString program_version_column_name , QString program_version_db_name, void UPGRADE_TO_VERSION_FUNC(QString) )
{
    SQL_QUERY query      ( DB );

    query.PREPARE_SELECT(program_version_db_name,program_version_column_name);

    if ( query.SELECT() EQ 0 ) {
        return;
    }
    query.NEXT();

    double program_version_in_db = query.VALUE(0).toDouble();
    double new_program_version   = ADAK_PROGRAM_VERSION(ADAK_VERITABANI_ID()).toDouble();

    if (program_version_in_db EQ new_program_version) {
        return;
    }

    if ( program_version_in_db > new_program_version ) {
        ADAK_ERROR("Bu programın versiyonu , veritabanının versiyonundan daha küçük. Programı güncelleyin , aksi taktirde verileriniz bozulur.",NULL,NULL);
        exit(77);
    }

    VERITABANLARINI_GUNCELLE();

    QSplashScreen * splash = CREATE_SPLASH_SCREEN();
    splash->show();
    splash->showMessage((QString("Programınızın versiyonu yükseltiliyor. Lütfen Bekleyiniz...")), Qt::AlignCenter, Qt::white );

    double current_program_version = program_version_in_db;

    DB->START_TRANSACTION();

    while ( current_program_version < new_program_version ) {        

        QString version = QVariant(current_program_version).toString();

        QStringList info = version.split(".",QString::SkipEmptyParts,Qt::CaseInsensitive);

        version.clear();

        if (info.size() NE 2) {
            version.append(info.at(0) + ".00");
        }
        else {
            if (info.at(1).size() NE 2) {
                version.append(info.at(0) + "." + info.at(1) + "0");
            }
            else {
                version.append(info.at(0) + "." + info.at(1));
            }
        }

        UPGRADE_TO_VERSION_FUNC(version);
        current_program_version = ROUND (current_program_version + 0.01);
    }

    query.PREPARE_UPDATE (program_version_db_name , "" , program_version_column_name , "");
    query.SET_VALUE ( QString(":%1").arg(program_version_column_name) , ADAK_PROGRAM_VERSION(ADAK_VERITABANI_ID()).toDouble());

    query.UPDATE();

    splash->finish(NULL);

    ADAK_WARNING("Programın versiyonu yükseltilmiştir.\n"
                "Yeni özellikler için lütfen Kullanıcı Yetkileri ' ni kontrol ediniz.\n"
                "Kullanıcı Yetkileri ' ni Kullanıcılar Ekranı ' ndan ayarlayabilirsiniz.\n\n"
                "Bazı hataları gidermek için Yönetim İşlemleri->E9 Onar ' ı kullanabilirsiniz."
                ,NULL,NULL);

    DB->COMMIT_TRANSACTION();
}


/**************************************************************************************
                   KULLANICI_SAYISI
***************************************************************************************/

int KULLANICI_SAYISI()
{
    if (G_YONETIM_DB EQ NULL) {
        return 0;
    }

    SQL_QUERY sql_query      ( G_YONETIM_DB );
    sql_query.PREPARE_SELECT ( "ynt_kullanicilar","kullanici_id","kullanici_id > 1 AND silinmis_mi = 0");
    sql_query.SELECT();

    return sql_query.NUM_OF_ROWS();
}


/**************************************************************************************
                   KAYITLI_KULLANICI_SAYISI
***************************************************************************************/

int KAYITLI_KULLANICI_SAYISI ()
{
    if (G_YONETIM_DB EQ NULL) {
       return 0;
    }

    SQL_QUERY sql_query ( G_YONETIM_DB );

    sql_query.PREPARE_SELECT ("ynt_kullanicilar","kullanici_id");

    return sql_query.SELECT();
}

/**************************************************************************************
                   VERITABANI_DEGISTIR
***************************************************************************************/

int VERITABANI_DEGISTIR ( ADAK_SQL ** p_program_db, QWidget * p_parent )
{
    QString veritabani_ismi;
    QString veritabani_tanimi;

    int veritabani_id = VERITABANI_SEC( KULLANICI_ID() , &veritabani_ismi , &veritabani_tanimi , (QDialog *)p_parent );

    ADAK_SQL * db_conn = CREATE_ADAK_SQL_CONNECTION( GET_PROGRAM_DB_STRUCTS() , SQL_DBNAME_ONEK() + "adak_" + veritabani_ismi , (*p_program_db)->GET_SQL_DRIVER_ENUM());

    if ( db_conn->CONNECT_TO_DATABASE( true ) EQ ADAK_OK ) {

        *p_program_db           = db_conn;

        SET_VERITABANI_ID       (veritabani_id);
        SET_VERITABANI_ISMI     (veritabani_ismi);
        SET_VERITABANI_TANIMI   (veritabani_tanimi);

        return veritabani_id;
    }

    return -1;
}

/**************************************************************************************
                   SISTEM_GET_MENU_STRUCT
***************************************************************************************/

MENU_STRUCT * SISTEM_GET_MENU_STRUCT()
{

    // SISTEM MENUSUNE YENE MENU EKLENIR VEYA SILINIRSE YONETIMDE DUZELTME YAPILMALI

    static struct MENU_STRUCT SISTEM_MENU_STRUCT[] = {

            { MENU_SIS_KULLANICILAR,           QObject::tr ("Kullanıcılar"),            "YNT1","","" ,false,1, 0 },
            { MENU_SIS_BILGISAYARLAR,          QObject::tr ("Bilgisayarlar"),           "YNT2","","" ,false,1, 0 },
            { MENU_SIS_VERITABANLARI,          QObject::tr ("Veritabanları"),           "YNT3","","",false,1 , 0 },
            { MENU_SEPERATOR,                  QObject::tr (""),                        "","","",false,1 , 0 },

            { MENU_SIS_KULLANICI_DEGISTIR ,    QObject::tr ("Kullanıcı Değiştir"),      "YNT4","","" ,false,1, 0 },
            { MENU_SIS_VERITABANI_DEGISTIR,    QObject::tr ("Veritabanı Değiştir"),     "YNT5","","" ,false,1, 0 },
            { MENU_SIS_SIFRE_DEGISTIR ,        QObject::tr ("Şifre Değiştir"),          "YNT6","","",false,1, 0 },
            { MENU_SEPERATOR,                  QObject::tr (""),                        "","","",false,1 , 0 },

            { MENU_SIS_POSTA_SUNUCUSU,         QObject::tr ("Posta Sunucusu Tanımlama"),"YNT7","","",false,1 , 0 },
            { MENU_SIS_SMS_SUNUCUSU        ,   QObject::tr ("SMS Sunucusu Tanımlama"),  "YNT8","","",false,1, 0 },
            { MENU_SEPERATOR,                  QObject::tr (""),                        "","","",false,1 , 0 },
            { MENU_SEPERATOR,                  QObject::tr (""),                        "","","",false,1 , 0 },
            { MENU_SIS_YONETIM_LOG_BILGILERI,  QObject::tr ("Yönetim Log Bilgileri"),   "YNT9","","" ,false,1, 0  },
            { MENU_SIS_HAKKIMIZDA,             QObject::tr ("Hakkında"),                "YNT10","","",false,1 , 0              },
            { MENU_SIS_OTOMATIK_SIFRE_URET,    QObject::tr ("Otomatik Şifreyi Üret"),   "YNT11","","" ,false,1, 0 },
            { MENU_SIS_OTOMATIK_GIRIS_KAPAT,   QObject::tr ("Otomatik Girişi Kapat"),   "YNT12","","" ,false,1, 0 },

            { MENU_END       , ""  , "" , "","",false,1,0}
    };

    return SISTEM_MENU_STRUCT;
}

/**************************************************************************************
                   SISTEM_ITEM_CLICKED
***************************************************************************************/

void SISTEM_ITEM_CLICKED(int menu_item, QWidget *parent, void    (*F_PROGRAM_KULLANICI_YETKILERI_FONK) ( int,bool *, QWidget * ) )
{
    switch ( menu_item ) {
        case MENU_SIS_KULLANICILAR:
            OPEN_KULLANICILAR_FORMU (  F_PROGRAM_KULLANICI_YETKILERI_FONK, parent );
            break;

        case MENU_SIS_BILGISAYARLAR:
            OPEN_BILGISAYARLAR_FORMU ( parent );
            break;

        case MENU_SIS_VERITABANLARI :
            OPEN_VERITABANLARI_FORMU ( parent );
            break;

        case MENU_SIS_YONETIM_LOG_BILGILERI:
            OPEN_YONETIM_007_ARAMA ( parent );
            break;

        case MENU_SIS_POSTA_SUNUCUSU:
            OPEN_POSTA_SUNUCUSU_FORMU ( parent );
            break;

        case MENU_SIS_SIFRE_DEGISTIR:
            OPEN_SIFRE_DEGISTIRME_BATCH(parent);
            break;

        case MENU_SIS_KULLANICI_DEGISTIR:
            //Burada 0 daima ilk pencere
            if ( KULLANICI_DEGISTIR ( NULL ) > 0 ) {

                SQL_QUERY sql_query ( G_YONETIM_DB );

                sql_query.PREPARE_SELECT( "ynt_kullanicilar" , "kullanici_kodu, kullanici_adi", "kullanici_id = :kullanici_id" );
                sql_query.SET_VALUE     (":kullanici_id", KULLANICI_ID());

                if ( sql_query.SELECT() > 0 ) {
                    sql_query.NEXT();
                    ADAK_INFO( "Kullanıcı değişikliği başarılı. Seçilen kullanıcı: "+ sql_query.VALUE(0).toString().toUtf8() + " " + sql_query.VALUE(1).toString().toUtf8(), NULL , NULL );
                    //Burada 0 daima ilk pencere
                    static_cast<SEKME_MENU_KERNEL *>(G_SEKME_MENU_KERNEL.at(0))->REFRESH_MENU_KERNEL();
                }
            }
            break;

        case MENU_SIS_VERITABANI_DEGISTIR: {
                //Burada 0 daima ilk pencere
                if ( VERITABANI_DEGISTIR ( &DB, NULL ) > 0 ) {
                    static_cast<SEKME_MENU_KERNEL *>(G_SEKME_MENU_KERNEL.at(0))->REFRESH_MENU_KERNEL();

                    //! FIRMNALARIN MALI YILI FARKLI OLABILIR.
                    SQL_QUERY query( DB );

                    query.PREPARE_SELECT( "e9_sabit_degerler", "mali_yil_ilk_tarih", "sabit_deger_id = :sabit_deger_id");
                    query.SET_VALUE     ( ":sabit_deger_id", 1 );

                    if ( query.SELECT() NE 0 ) {
                        query.NEXT();

                         QDate mali_yil_ilk_tarih = QDate::fromString( query.VALUE( 0 ).toString(), "yyyy.MM.dd");
                         SET_MALI_YIL_FIRST_DATE ( mali_yil_ilk_tarih );
                    }
                    //! end
                }
            }
            break;

        case MENU_SIS_SMS_SUNUCUSU:
            OPEN_SMS_SUNUCUSU_FORMU(parent);
            break;
        case MENU_SIS_OTOMATIK_GIRIS_KAPAT:{
                QSettings settings ( "ADAK_SETTINGS", ADAK_PROGRAM_SHORTNAME(ADAK_DISPLAY_ID()));
                settings.setValue( "is_auto_login", false );

                ADAK_INFO( QObject::tr("Otomatik Giriş İptal edildi..."), NULL, parent );
                static_cast<SEKME_MENU_KERNEL *>(G_SEKME_MENU_KERNEL.at(0));

            }
            break;

        case MENU_SIS_OTOMATIK_SIFRE_URET:{
                ADAK_INFO( QObject::tr("SQL Kullanıcı Şifresi<br><br> "
                      "<b>%1</b><br><br>"
                      "Dikkat: Bu Şifreyi Veritabanında oluşturduğunuz kullanıcıya atayın.").arg( SQL_DEFAULT_PASSWORD() ), NULL, NULL );
            break;
        }
        case MENU_SIS_HAKKIMIZDA :{
            OPEN_YONETIM_HAKKIMIZDA( parent );
            break;
        }
        default:
            break;
    }
}
