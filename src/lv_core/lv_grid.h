/**
 * @file lv_grid.h
 *
 */

#ifndef LV_GRID_H
#define LV_GRID_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_misc/lv_area.h"

/*********************
 *      DEFINES
 *********************/

#define LV_GRID_START               0
#define LV_GRID_CENTER              1
#define LV_GRID_END                 2
#define LV_GRID_STRETCH             3
#define LV_GRID_SPACE_EVENLY        4
#define LV_GRID_SPACE_AROUND        5
#define LV_GRID_SPACE_BETWEEN       6

/**
 * Some helper defines
 * */
#define _GRID_IS_CELL(c)        ((c) >= LV_COORD_MAX ? true : false)
#define _GRID_CELL_SHIFT        5
#define _GRID_CELL_MAX          ((1 << _GRID_CELL_SHIFT) - 1)
#define _GRID_CELL_POS_MASK     ((1 << _GRID_CELL_SHIFT) - 1)
#define _GRID_CELL_SPAN_MASK    (_GRID_CELL_POS_MASK << _GRID_CELL_SHIFT)
#define _GRID_CELL_FLAG_MASK    (_GRID_CELL_POS_MASK << (2 * _GRID_CELL_SHIFT))
#define _GRID_CELL_FLAG(b)      ((b) << (_GRID_CELL_SHIFT * 2))
#define _GRID_CELL_AUTO         _GRID_CELL_MAX
#define _GRID_GET_CELL_POS(c)   ((c) & _GRID_CELL_POS_MASK)
#define _GRID_GET_CELL_SPAN(c)  (((c) & _GRID_CELL_SPAN_MASK) >> _GRID_CELL_SHIFT)
#define _GRID_GET_CELL_FLAG(c)  ((c) >> (_GRID_CELL_SHIFT * 2) & 0x3)

#define _GRID_CELL_SIZE_PX    0     /* The cell size is set in pixels*/
#define _GRID_CELL_SIZE_FR    1     /* The cell size is set in free units*/

#define _GRID_FR_MAX            256
#define _GRID_FILL_MAX          2048
#define _GRID_REPEAT_MAX           2048
#define _GRID_FR_START        (LV_COORD_MAX)
#define _GRID_FILL_START      (_GRID_FR_START + _GRID_FR_MAX)
#define _GRID_REPEAT_START    (_GRID_FILL_START + _GRID_FILL_MAX)

#define LV_GRID_FR(x)     (_GRID_FR_START + (x))
#define LV_GRID_FILL(x)   (_GRID_FILL_START + (x))
#define LV_GRID_REPEAT(x) (_GRID_REPEAT_START + (x))
#define LV_GRID_REPEAT_FIT (_GRID_REPEAT_START + _GRID_REPEAT_MAX - 1)

#define _GRID_IS_PX(x)      ((_GRID_IS_FR(x) == false) && (_GRID_IS_AUTO(x) == false) ? true : false)
#define _GRID_IS_FR(x)      ((x) > _GRID_FR_START && (x) <  _GRID_FILL_START ? true : false)
#define _GRID_IS_FILL(x)    ((x) > _GRID_FILL_START && (x) < _GRID_REPEAT_START ? true : false)
#define _GRID_IS_REPEAT(x)  ((x) > _GRID_REPEAT_START  ? true : false)
#define _GRID_IS_AUTO(x)    (x == LV_GRID_AUTO ? true : false)
#define _GRID_GET_FR(x)     ((x) - LV_COORD_MAX)
#define _GRID_GET_FILL(x)     ((x) - _GRID_FILL_START)
#define _GRID_GET_REPEAT(x)     ((x) - _GRID_REPEAT_START)


/**
 * Define a grid cell with position and span.
 * Can be used like `lv_obj_set_pos(btn, LV_GRID_CELL(3,2), LV_GRID_CELL(2,1))`
 */
#define LV_GRID_CELL_START(pos, span)   ((LV_COORD_MAX + (pos) + (span << _GRID_CELL_SHIFT)) | _GRID_CELL_FLAG(LV_GRID_START))
#define LV_GRID_CELL_END(pos, span)     ((LV_COORD_MAX + (pos) + (span << _GRID_CELL_SHIFT)) | _GRID_CELL_FLAG(LV_GRID_END))
#define LV_GRID_CELL_CENTER(pos, span)  ((LV_COORD_MAX + (pos) + (span << _GRID_CELL_SHIFT)) | _GRID_CELL_FLAG(LV_GRID_CENTER))
#define LV_GRID_CELL_STRETCH(pos, span) ((LV_COORD_MAX + (pos) + (span << _GRID_CELL_SHIFT)) | _GRID_CELL_FLAG(LV_GRID_STRETCH))
/**
 * Special LV_GRID_CELL position to flow the object automatically.
 * Both X (column) and Y (row) value needs to be AUTO or explicitly specified*/
#define LV_GRID_AUTO_START      LV_GRID_CELL_START(_GRID_CELL_AUTO, 0)
#define LV_GRID_AUTO_END        LV_GRID_CELL_END(_GRID_CELL_AUTO, 0)
#define LV_GRID_AUTO_CENTER     LV_GRID_CELL_CENTER(_GRID_CELL_AUTO, 0)
#define LV_GRID_AUTO_STRETCH    LV_GRID_CELL_STRETCH(_GRID_CELL_AUTO, 0)

/**********************
 *      TYPEDEFS
 **********************/

/* Can't include lv_obj.h because it includes this header file */
struct _lv_obj_t;
typedef struct _lv_obj_t lv_obj_t;

typedef struct {
    const lv_coord_t * col_dsc;
    const lv_coord_t * row_dsc;
    uint8_t col_dsc_len;
    uint8_t row_dsc_len;
    lv_coord_t col_gap;
    lv_coord_t row_gap;
    uint8_t col_place;
    uint8_t row_place;
}lv_grid_t;

typedef struct {
    lv_coord_t * x;
    lv_coord_t * y;
    lv_coord_t * w;
    lv_coord_t * h;
    uint32_t col_num;
    uint32_t row_num;
    lv_coord_t grid_w;
    lv_coord_t grid_h;
}_lv_grid_calc_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_grid_init(lv_grid_t * grid);

void lv_grid_set_template(lv_grid_t * grid, const lv_coord_t * col_dsc, const lv_coord_t * row_dsc);

void lv_grid_set_place_content(lv_grid_t * grid, uint8_t col_place, uint8_t row_place);

/**
 * Set a grid for an object
 * @param obj pointer to an object
 * @param grid the grid to set
 */
void lv_obj_set_grid(lv_obj_t * obj, const lv_grid_t * grid);

/**
 * Get the grid of an object
 * @param obj pointer to an object
 * @return the grid, NULL if no grid
 */
const lv_grid_t * lv_obj_get_grid(lv_obj_t * obj, const lv_grid_t * grid);


/**
 * Notify all object if a style is modified
 * @param grid pointer to a grid. Only the objects with this grid will be notified
 *               (NULL to notify all objects with any grid)
 */
void lv_obj_report_grid_change(const lv_grid_t * grid);

void _lv_grid_calc(struct _lv_obj_t * obj, _lv_grid_calc_t * calc);

void _lv_grid_calc_free(_lv_grid_calc_t * calc);

bool _lv_grid_has_fr_col(struct _lv_obj_t * obj);

bool _lv_grid_has_fr_row(struct _lv_obj_t * obj);


/**
 * Check if the object's grid columns are "fill" type
 * @param obj pointer to an object
 * @return true: fill type; false: not fill type
 */
bool _lv_grid_has_fill_col(struct _lv_obj_t * obj);
/**
 * Check if the object's grid rows are "fill" type
 * @param obj pointer to an object
 * @return true: fill type; false: not fill type
 */
bool _lv_grid_has_fill_row(struct _lv_obj_t * obj);

void _lv_grid_full_refresh(lv_obj_t * cont);

void lv_grid_item_refr_pos(lv_obj_t * item);


/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_GRID_H*/