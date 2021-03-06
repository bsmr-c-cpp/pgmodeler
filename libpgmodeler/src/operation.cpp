/*
# PostgreSQL Database Modeler (pgModeler)
#
# Copyright 2006-2016 - Raphael Araújo e Silva <raphael@pgmodeler.com.br>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# The complete text of GPLv3 is at LICENSE file on source code root directory.
# Also, you can get the complete GNU General Public License at <http://www.gnu.org/licenses/>
*/

#include "operation.h"

Operation::Operation(void)
{
	parent_obj=nullptr;
	pool_obj=nullptr;
	original_obj=nullptr;
	object_idx=-1;
	chain_type=NO_CHAIN;
	op_type=NO_OPERATION;
}

QString Operation::generateOperationId(void)
{
	QString addr;
	QTextStream stream(&addr);
	QCryptographicHash hash(QCryptographicHash::Md5);

	//Stores the permission address on a string
	stream << reinterpret_cast<unsigned *>(original_obj);
	stream << reinterpret_cast<unsigned *>(pool_obj);
	stream << reinterpret_cast<unsigned *>(parent_obj);

	//Generates an unique id through md5 hash
	hash.addData(QByteArray(addr.toStdString().c_str()));
	return(hash.result().toHex());
}

void Operation::setObjectIndex(int idx)
{
	object_idx=idx;
}

void Operation::setChainType(unsigned type)
{
	chain_type=(type > CHAIN_END ? NO_CHAIN : type);
}

void Operation::setOperationType(unsigned type)
{
	op_type=(type > OBJECT_MOVED ? NO_OPERATION : type);
}

void Operation::setOriginalObject(BaseObject *object)
{
	original_obj=object;
	operation_id=generateOperationId();
}

void Operation::setPoolObject(BaseObject *object)
{
	pool_obj=object;
	operation_id=generateOperationId();
}

void Operation::setParentObject(BaseObject *object)
{
	parent_obj=object;
	operation_id=generateOperationId();
}

void Operation::setPermissions(const vector<Permission *> &perms)
{
	permissions=perms;
}

void Operation::setXMLDefinition(const QString &xml_def)
{
	xml_definition=xml_def;
}

int Operation::getObjectIndex(void)
{
	return(object_idx);
}

unsigned Operation::getChainType(void)
{
	return(chain_type);
}

unsigned Operation::getOperationType(void)
{
	return(op_type);
}

BaseObject *Operation::getOriginalObject(void)
{
	return(original_obj);
}

BaseObject *Operation::getPoolObject(void)
{
	return(pool_obj);
}

BaseObject *Operation::getParentObject(void)
{
	return(parent_obj);
}

vector<Permission *> Operation::getPermissions(void)
{
	return(permissions);
}

QString Operation::getXMLDefinition(void)
{
	return(xml_definition);
}

bool Operation::isOperationValid(void)
{
	return(operation_id==generateOperationId());
}
