#ifndef SQL_TABLOLAR_FISI_H
#define SQL_TABLOLAR_FISI_H

#include "fis_kernel.h"

namespace Ui {
    class SQL_TABLOLAR_FISI;
}

class SQL_TABLOLAR_FISI : public FIS_KERNEL

{
    Q_OBJECT;

public:

     SQL_TABLOLAR_FISI                                                  ( QWidget *parent = 0 );
    ~SQL_TABLOLAR_FISI                                                  (){}

private:

    Ui::SQL_TABLOLAR_FISI     *      m_ui;

    int                     num_of_columns;

    void                    SETUP_FORM                               ();
    void                    CLEAR_FORM_MEMBERS                       ();
    void                    NEW_FIS_RECORD                           ();
    int                     GET_FIS_RECORD                           (int tablo_id);

    int                     CHECK_FIS_FORM_VAR                       (QObject * object);
    int                     CHECK_FIS_FORM_EMPTY                     ();

    int                     CHECK_FIS_RECORD_ADD                     ();
    int                     ADD_FIS_RECORD                           ();
    int                     CHECK_FIS_RECORD_UPDATE                  (int tablo_id);
    void                    UPDATE_FIS_RECORD                        (int tablo_id);
    int                     CHECK_FIS_RECORD_DELETE                  (int tablo_id);
    void                    DELETE_FIS_RECORD                        (int tablo_id);

    int                     SELECT_FIS_RECORD                        ();
    int                     FIND_FIS_RECORD                          ();
    int                     FIND_NEXT_FIS_RECORD                     ();
    int                     FIND_PREV_FIS_RECORD                     ();
    int                     FIND_FIRST_FIS_RECORD                    ();
    int                     FIND_LAST_FIS_RECORD                     ();

    int                     LOCK_FIS_RECORD                          (int p_tablo_id);
    void                    UNLOCK_FIS_RECORD                        (int p_tablo_id);

    void                    SET_LINE_DEFAULTS                        ( int row_number );
    int                     CHECK_LINE_VAR                           ( int row_number, QObject * object );
    int                     CHECK_LINE_EMPTY                         ( int row_number );
    int                     CHECK_ADD_LINE                           ( int tablo_id, int row_number );
    void                    ADD_LINE                                 ( int tablo_id, int row_number );
    int                     CHECK_UPDATE_LINE                        ( int tablo_id, int row_number );
    void                    UPDATE_LINE                              ( int tablo_id, int row_number );
    int                     CHECK_DELETE_LINE                        ( int tablo_id, int row_number );
    void                    DELETE_LINE                              ( int tablo_id, int row_number );

    void                    SAVER_BUTTON_CLICKED                     ( QAbstractButton * button, int tablo_id );


};

#endif // SQL_TABLOLAR_FISI_H
