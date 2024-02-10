-- VoxForge deps
include "./Scripts/Premake/Containers/ordered_pairs.lua"
include "./Scripts/Premake/Utils/FirstToUpper.lua"


-- Dependencies table
Dependencies = {

}


-- Linking
function Link(table, isDebug, target)
    -- Setup lib dir
    if table.LibDir ~= nil then
        libdirs { table.LibDir }
    end

    -- Try linking
    local libraryName = nil
	if table.LibName ~= nil then
		libraryName = table.LibName
	end

	if table.DebugLibName ~= nil and is_debug and target == "Windows" then
		libraryName = table.DebugLibName
	end

	if libraryName ~= nil then
		links { libraryName }
		return true
	end

	return false
end


-- Adding dependency includes
function AddIncludes(table)
    if table.IncludeDir ~= nil then
        externalincludedirs { table.IncludeDir }
    end
end


-- Process dependencies
function ProcessDependencies(config_name)
    local target = FirstToUpper(os.target())

    for key, libraryData in orderedPairs(Dependencies) do

        -- Always match config_name if no Configurations list is specified
        local matchesConfiguration = true

        if config_name ~= nil and libraryData.Configurations ~= nil then
            matchesConfiguration = string.find(libraryData.Configurations, config_name)
        end

        local isDebug = config_name == "Debug"

        if matchesConfiguration then
            local continueLink = true

            -- Process Platform Scope
            if libraryData[target] ~= nil then
                continueLink = not Link(libraryData[target], isDebug, target)
                AddIncludes(libraryData[target])
            end

            -- Process Global Scope
            if continueLink then
                Link(libraryData, isDebug, target)
            end

            AddIncludes(libraryData)
        end

    end
end


-- Include dependencies
function IncludeDependencies(config_name)
    local target = FirstToUpper(os.target())

    for key, libraryData in orderedPairs(Dependencies) do

        -- Always match config_name if no Configurations list is specified
        local matchesConfiguration = true

        if config_name ~= nil and libraryData.Configurations ~= nil then
            matchesConfiguration = string.find(libraryData.Configurations, config_name)
        end

        local isDebug = config_name == "Debug"

        if matchesConfiguration then
            local continueLink = true

            -- Process Platform Scope
            if libraryData[target] ~= nil then
                continueLink = not Link(libraryData[target], isDebug, target)
                AddIncludes(libraryData[target])
            end

            -- Process Global Scope
            if continueLink then
                Link(libraryData, isDebug, target)
            end

            AddIncludes(libraryData)
        end

    end
end