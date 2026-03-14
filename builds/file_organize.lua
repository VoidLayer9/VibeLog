function file_organize()


    local sand_box_content = ""
    local sandbox_files = darwin.dtw.list_files_recursively("sandbox", true)
    for i=1,#sandbox_files do
        local current = sandbox_files[i]
        sand_box_content = sand_box_content .. "\n#include \"" .. current .. "\""
    end 
    local content = darwin.mdeclare.transform_dir({
        dir="wrapper",
        startswith="fdefine",
        endswith=".c",
    })

    darwin.dtw.write_file("wrapper/fdeclare.all.h", content)
    darwin.silverchain.remove("wrapper/fdeclare.all.h")

    darwin.silverchain.generate({
        src = "wrapper",
        project_short_cut = PROJECT_NAME,
        tags = { 
            "dep_declare",
            "macros",
            "types",
            "consts",
            "fdeclare",
            'globals',
            "fdefine",
            "dep_define"
            
    }})
end 

darwin.add_recipe({
    inputs={
        "wrapper",
        "dependencies"
    },
    outs= {
        "wrapper/fdeclare.all.h"
    },
    name="file_organize",
    description = "Organize source files using SilverChain",
    callback = file_organize
})