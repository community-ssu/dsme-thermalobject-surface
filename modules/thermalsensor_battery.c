/**
   @file thermalsensor_battery.c

   This module provides battery temperature readings.
   <p>
   Copyright (C) 2009 Nokia Corporation
   Copyright (C) 2012 Pali Rohár <pali.rohar@gmail.com>

   @author Semi Malinen <semi.malinen@nokia.com>

   This file is part of Dsme.

   Dsme is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 2.1 as published by the Free Software Foundation.

   Dsme is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Dsme.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "thermalsensor_battery.h"
#include "dsme/logging.h"
#include <glib.h>
#include <string.h>

#define BQ27200_TEMP_PATH "/sys/class/power_supply/bq27200-0/temp"

void*       the_cookie;
void      (*report_temperature)(void* cookie, int temperature);

static gboolean read_temperature(gpointer data)
{
  FILE *fp = data;
  int temp;
  int ret;

  if (!fp)
    return false;

  ret = fscanf(fp, "%d", &temp);

  fclose(fp);

  if (ret != 1)
  {
    /* use temperature -1 to indicate that the request failed */
    report_temperature(the_cookie, -1);
    return false;
  }

  /* dsme accept only milidegrees celsius or degress kelvin */
  /* convert 1/100 degrees celsius to kelvin */
  temp = temp/100+273;

  report_temperature(the_cookie, temp);
  return false;
}

extern bool dsme_request_battery_temperature(
                void* cookie,
                void (callback)(void* cookie, int temperature))
{
  FILE *fp = fopen(BQ27200_TEMP_PATH, "r");

  if (!fp)
    return false;

  the_cookie         = cookie;
  report_temperature = callback;

  /* make sure that callback will be called after function returns */
  g_timeout_add_seconds(0, read_temperature, fp);

  return true;
}
