/******************************************************************************
 *
 *  $Id$
 *
 *  Copyright (C) 2006  Florian Pose, Ingenieurgemeinschaft IgH
 *
 *  This file is part of the IgH EtherCAT Master.
 *
 *  The IgH EtherCAT Master is free software; you can redistribute it
 *  and/or modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  The IgH EtherCAT Master is distributed in the hope that it will be
 *  useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the IgH EtherCAT Master; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  The right to use EtherCAT Technology is granted and comes free of
 *  charge under condition of compatibility of product made by
 *  Licensee. People intending to distribute/sell products based on the
 *  code, have to sign an agreement to guarantee that products using
 *  software based on IgH EtherCAT master stay compatible with the actual
 *  EtherCAT specification (which are released themselves as an open
 *  standard) as the (only) precondition to have the right to use EtherCAT
 *  Technology, IP and trade marks.
 *
 *****************************************************************************/

/**
   \file
   EtherCAT finite state machines.
*/

/*****************************************************************************/

#ifndef __EC_FSM_MASTER__
#define __EC_FSM_MASTER__

#include "globals.h"
#include "../include/ecrt.h"
#include "datagram.h"
#include "slave.h"
#include "canopen.h"

#include "fsm_slave.h"

/*****************************************************************************/

typedef struct ec_fsm_master ec_fsm_master_t; /**< \see ec_fsm_master */

/**
   Finite state machine of an EtherCAT master.
*/

struct ec_fsm_master
{
    ec_master_t *master; /**< master the FSM runs on */
    ec_datagram_t *datagram; /**< datagram used in the state machine */
    unsigned int retries; /**< retries on datagram timeout. */

    void (*state)(ec_fsm_master_t *); /**< master state function */
    unsigned int slaves_responding; /**< number of responding slaves */
    ec_slave_state_t slave_states; /**< states of responding slaves */
    unsigned int validate; /**< non-zero, if validation to do */
    ec_slave_t *slave; /**< current slave */
    ec_sdo_request_t *sdo_request; /**< SDO request to process */
    uint16_t sii_offset; 

    ec_fsm_slave_t fsm_slave; /**< slave state machine */
    ec_fsm_sii_t fsm_sii; /**< SII state machine */
    ec_fsm_change_t fsm_change; /**< State change state machine */
    ec_fsm_coe_t fsm_coe; /**< CoE state machine */
};

/*****************************************************************************/

void ec_fsm_master_init(ec_fsm_master_t *, ec_master_t *, ec_datagram_t *);
void ec_fsm_master_clear(ec_fsm_master_t *);

int ec_fsm_master_exec(ec_fsm_master_t *);
int ec_fsm_master_running(ec_fsm_master_t *);
int ec_fsm_master_success(ec_fsm_master_t *);

/*****************************************************************************/

#endif
