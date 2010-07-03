/* EINA - EFL data type library
 * Copyright (C) 2008 Gustavo Sverzut Barbieri
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EINA_SAFETY_CHECKS_H_
#define EINA_SAFETY_CHECKS_H_

/**
 * @addtogroup Eina_Tools_Group Tools
 *
 * @{
 */

/**
 * @defgroup Eina_Safety_Checks_Group Safety Checks
 *
 * @warning @c eina_safety_checks.h should only be included by source
 *          files, after all other includes and before the source file
 *          specific includes. By source file specific includes we
 *          mean those that define the functions that are being
 *          checked. The reason for such complexity is the trick to
 *          avoid compiler optimizations. If compilers are told that
 *          some given function will never receive @c NULL
 *          (EINA_ARG_NONNULL(), then compiler will emit a warning if
 *          it detects so (good!) but will remove any checks for that
 *          condition as it believes it will never happen, removing
 *          all safety checks! By including @c eina_safety_checks.h it
 *          will redefine EINA_ARG_NONNULL() to void and compiler
 *          warning will not be emitted, but checks will be there. The
 *          files already processed with the old macro
 *          EINA_ARG_NONNULL() will still work and emit the warnings.
 *
 *
 * @code
 *
 * // all these files will emit warning from EINA_ARG_NONNULL()
 * #include <Evas.h>  // third party headers
 * #include <Ecore.h>
 * #include <eina_error.h> // eina own header
 *
 * #include <eina_safety_checks.h>
 * // all these files below will NOT emit warning from EINA_ARG_NONNULL(),
 * // but this is required to have the functions defined there to be checked
 * // for NULL pointers
 * #include "my_functions1.h"
 * #include "my_functions2.h"
 *
 * @endcode
 *
 * @{
 */


#include "eina_config.h"
#include "eina_error.h"

/**
 * @var EINA_ERROR_SAFETY_FAILED
 * Error identifier corresponding to safety check failure.
 */
EAPI extern Eina_Error EINA_ERROR_SAFETY_FAILED;

#ifdef EINA_SAFETY_CHECKS

#include "eina_log.h"

#define EINA_SAFETY_ON_NULL_RETURN(exp)					\
  do									\
    {									\
       if (EINA_UNLIKELY((exp) == NULL))				\
	 {								\
	    eina_error_set(EINA_ERROR_SAFETY_FAILED);			\
	    EINA_LOG_ERR("%s", "safety check failed: " #exp " == NULL"); \
	    return;							\
	 }								\
    }									\
  while (0)

#define EINA_SAFETY_ON_NULL_RETURN_VAL(exp, val)			\
  do									\
    {									\
       if (EINA_UNLIKELY((exp) == NULL))				\
	 {								\
	    eina_error_set(EINA_ERROR_SAFETY_FAILED);			\
	    EINA_LOG_ERR("%s", "safety check failed: " #exp " == NULL"); \
	    return (val);						\
	 }								\
    }									\
  while (0)

#define EINA_SAFETY_ON_TRUE_RETURN(exp)					\
  do									\
    {									\
       if (EINA_UNLIKELY(exp))						\
	 {								\
	    eina_error_set(EINA_ERROR_SAFETY_FAILED);			\
	    EINA_LOG_ERR("%s", "safety check failed: " #exp " is true"); \
	    return;							\
	 }								\
    }									\
  while (0)

#define EINA_SAFETY_ON_TRUE_RETURN_VAL(exp, val)			\
  do									\
    {									\
       if (EINA_UNLIKELY(exp))						\
	 {								\
	    eina_error_set(EINA_ERROR_SAFETY_FAILED);			\
	    EINA_LOG_ERR("%s", "safety check failed: " #exp " is true"); \
	    return val;							\
	 }								\
    }									\
  while (0)

#define EINA_SAFETY_ON_TRUE_GOTO(exp, label)				\
  do									\
    {									\
       if (EINA_UNLIKELY(exp))						\
	 {								\
	    eina_error_set(EINA_ERROR_SAFETY_FAILED);			\
	    EINA_LOG_ERR("%s", "safety check failed: " #exp " is true"); \
	    goto label;							\
	 }								\
    }									\
  while (0)

#define EINA_SAFETY_ON_FALSE_RETURN(exp)				\
  do									\
    {									\
       if (EINA_UNLIKELY(!(exp)))					\
	 {								\
	    eina_error_set(EINA_ERROR_SAFETY_FAILED);			\
	    EINA_LOG_ERR("%s", "safety check failed: " #exp " is false"); \
	    return;							\
	 }								\
    }									\
  while (0)

#define EINA_SAFETY_ON_FALSE_RETURN_VAL(exp, val)			\
  do									\
    {									\
       if (EINA_UNLIKELY(!(exp)))					\
	 {								\
	    eina_error_set(EINA_ERROR_SAFETY_FAILED);			\
	    EINA_LOG_ERR("%s", "safety check failed: " #exp " is false"); \
	    return val;							\
	 }								\
    }									\
  while (0)

#define EINA_SAFETY_ON_FALSE_GOTO(exp, label)				\
  do									\
    {									\
       if (EINA_UNLIKELY(!(exp)))					\
	 {								\
	    eina_error_set(EINA_ERROR_SAFETY_FAILED);			\
	    EINA_LOG_ERR("%s", "safety check failed: " #exp " is false"); \
	    goto label;							\
	 }								\
    }									\
  while (0)

#ifdef EINA_ARG_NONNULL
/* make EINA_ARG_NONNULL void so GCC does not optimize safety checks */
#undef EINA_ARG_NONNULL
#define EINA_ARG_NONNULL(idx, ...)
#endif


#else /* no safety checks */

#define EINA_SAFETY_ON_NULL_RETURN(exp)					\
  do { (void)((exp) == NULL); } while (0)

#define EINA_SAFETY_ON_NULL_RETURN_VAL(exp, val)			\
  do { if (0 && (exp) == NULL) (void)val; } while (0)

#define EINA_SAFETY_ON_TRUE_RETURN(exp)					\
  do { (void)(exp); } while (0)

#define EINA_SAFETY_ON_TRUE_RETURN_VAL(exp, val)			\
  do { if (0 && (exp)) (void)val; } while (0)

#define EINA_SAFETY_ON_FALSE_RETURN(exp)				\
  do { (void)(!(exp)); } while (0)

#define EINA_SAFETY_ON_FALSE_RETURN_VAL(exp, val)			\
  do { if (0 && !(exp)) (void)val; } while (0)

#endif /* safety checks macros */
#endif /* EINA_SAFETY_CHECKS_H_ */

/**
 * @}
 */

/**
 * @}
 */
