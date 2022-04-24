--------------------------------------------------------------------------------
--- LuaSTG Sub 文件管理
--- 璀境石
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--- 压缩包

---@class lstg.Archive
local C = {}

---判断压缩包是否还有效，可能压缩包本身已经被卸载但是引用还在
---@return boolean
function C:IsValid()
end

---判断压缩包是否存在指定的文件
---@param filepath string @文件在压缩包内的路径
---@return boolean
function C:FileExist(filepath)
end

---列出指定路径内所有的文件和文件夹
---@param searchpath string @搜索路径
---@param extend string|nil @如果该参数存在，则匹配文件拓展名，并且屏蔽文件夹，只保留文件
---@return table<number, table> @返回的表中，每个元素为普通的表，第一项是文件或文件夹的完整路径，第二项为boolean值，为true时代表该项为文件夹
function C:EnumFiles(searchpath, extend)
    return {{"sample.ext",false}, {"sampledir/",true}}
end

---列出压缩包内所有的文件和文件夹
---@return table<number, table> @返回的表中，每个元素为普通的表，第一项是文件或文件夹的完整路径，第二项为boolean值，为true时代表该项为文件夹
function C:ListFiles()
    return {{"sample.ext",false}, {"sampledir/",true}}
end

---获取压缩包名，请参考lstg.FileManager.LoadArchive第一个参数
---@return string
function C:GetName()
end

---获取压缩包优先级
---@return number
function C:GetPriority()
end

---设置压缩包优先级
---@param priority number
function C:SetPriority(priority)
end

--------------------------------------------------------------------------------
--- 文件管理

---@class lstg.FileManager
local M = {}
lstg.FileManager = M

---加载压缩包
---@param archivefilepath string @压缩包文件路径
---@param priority number|nil @可选参数，默认为0，压缩包优先级，必须为整数
---@param password string|nil @可选参数，默认为空(nil)，压缩包密码
---@return lstg.Archive|nil @如果加载成功，返回一个压缩包对象，否则返回空值
function M.LoadArchive(archivefilepath, priority, password)
end

---卸载压缩包
---@param archivefilepath string @压缩包文件路径，请参考lstg.FileManager.LoadArchive第一个参数
---@return boolean @返回的boolean值为true时，表示卸载该压缩包前，该压缩包确实已加载并卸载该压缩包，否则不存在且不进行任何操作
function M.UnloadArchive(archivefilepath)
end

---卸载所有已加载的压缩包
---@return nil @该方法没有返回值
function M.UnloadAllArchive()
end

---判断指定压缩包是否已经加载
---@param archivename string @压缩包名，请参考lstg.FileManager.LoadArchive第一个参数，另可参考lstg.Archive:GetName的返回值
---@return boolean
function M.ArchiveExist(archivename)
end

---枚举已经加载的压缩包
---@return table<number, table> @返回的表中，每个元素为普通的表，第一项是压缩包名，第二项为压缩包优先级
function M.EnumArchives()
    return {{"sample.zip", 0}, {"foo.zip", 9961}}
end

---获取已加载的压缩包，返回lstg.Archive对象
---@param archivename string @压缩包名，请参考lstg.FileManager.LoadArchive第一个参数，另可参考lstg.Archive:GetName的返回值
---@return lstg.Archive
function M.GetArchive(archivename)
end

--------------------------------------------------------------------------------
--- 文件判断和文件枚举

---判断指定的文件是否存在，只判断文件系统中的文件
---@param filepath string @文件
---@return boolean
function M.FileExist(filepath)
end

---判断指定的文件是否存在，除了判断文件系统中的文件外，还判断已加载的压缩包中的文件
---@param filepath string @文件
---@return boolean
function M.FileExistEx(filepath)
end

---列出指定路径内所有的文件和文件夹，仅搜索文件系统中的，不包括压缩包中的
---@param searchpath string @搜索路径
---@param extend string|nil @如果该参数存在，则匹配文件拓展名，并且屏蔽文件夹，只保留文件
---@return table<number, table> @返回的表中，每个元素为普通的表，第一项是文件或文件夹的完整路径，第二项为boolean值，为true时代表该项为文件夹
function M.EnumFiles(searchpath, extend)
    return {{"sample.ext",false}, {"sampledir/",true}}
end

---列出指定路径内所有的文件和文件夹，包括加载的压缩包中的
---@param searchpath string @搜索路径
---@param extend string|nil @如果该参数存在，则匹配文件拓展名，并且屏蔽文件夹，只保留文件
---@return table<number, table> @返回的表中，每个元素为普通的表，第一项是文件或文件夹的完整路径，第二项为boolean值，为true时代表该项为文件夹
function M.EnumFilesEx(searchpath, extend)
    return {{"sample.ext",false, nil}, {"sampledir/",true, "sample.zip"}}
end

--------------------------------------------------------------------------------
--- 搜索路径管理
--- 引擎在加载 Lua 脚本、图片文件、音频文件等资源的时候会从搜索路径中查找
--- Search path management
--- The engine will find from the search path when loading Lua scripts, texture files, audio files...

--- [LuaSTG Sub v0.10.0 新增]  
--- 添加搜索路径条目  
--- [LuaSTG Sub v0.10.0 Add]  
--- Add a search path  
---@param search_path string
function M.AddSearchPath(search_path)
end

--- [LuaSTG Sub v0.10.0 新增]  
--- 移除搜索路径条目  
--- [LuaSTG Sub v0.10.0 Add]  
--- Remove a search path  
---@param search_path string
function M.RemoveSearchPath(search_path)
end

--- [LuaSTG Sub v0.10.0 新增]  
--- 移除所有搜索路径条目  
--- [LuaSTG Sub v0.10.0 Add]  
--- Remove all search path  
function M.ClearSearchPath()
end

--------------------------------------------------------------------------------
--- 文件夹管理（不影响资源包内的文件夹）
--- Directory management (not affecting directories in archive)

--- [LuaSTG Sub v0.15.5 新增]  
--- 创建文件夹，可以是多级文件夹  
--- [LuaSTG Sub v0.15.5 Add]  
--- Create directories for every element of dirs that does not already exist  
---@param dirs string
---@return boolean
function M.CreateDirectory(dirs)
end

--- [LuaSTG Sub v0.15.5 新增]  
--- 递归删除文件夹，会删除所有子文件夹和包含的所有文件  
--- [LuaSTG Sub v0.15.5 Add]  
--- Deleta a directory recursively, delete all subdirectory and all files contained in  
---@param path string
---@return boolean
function M.RemoveDirectory(path)
end

return M
