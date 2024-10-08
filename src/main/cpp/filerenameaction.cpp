/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <log4cxx/logstring.h>
#include <log4cxx/rolling/filerenameaction.h>
#include <log4cxx/private/action_priv.h>

using namespace LOG4CXX_NS;
using namespace LOG4CXX_NS::rolling;
using namespace LOG4CXX_NS::helpers;

#define priv static_cast<FileRenameActionPrivate*>(m_priv.get())

struct FileRenameAction::FileRenameActionPrivate : public ActionPrivate
{
	FileRenameActionPrivate( const File& toRename,
		const File& renameTo,
		bool renameEmptyFile1):
		source(toRename), destination(renameTo), renameEmptyFile(renameEmptyFile1) {}

	const File source;
	const File destination;
	bool renameEmptyFile;
};

IMPLEMENT_LOG4CXX_OBJECT(FileRenameAction)

FileRenameAction::FileRenameAction(const File& toRename,
	const File& renameTo,
	bool renameEmptyFile1)
	: Action( std::make_unique<FileRenameActionPrivate>(toRename, renameTo, renameEmptyFile1) )
{
}

bool FileRenameAction::execute(LOG4CXX_NS::helpers::Pool& pool1) const
{
	return priv->source.renameTo(priv->destination, pool1);
}
