add_library(nuke_ui STATIC)

target_sources(nuke_ui PRIVATE
    # Main window
    main_window.cpp
    
    # Panels
    panels/node_graph_panel.cpp
    panels/properties_panel.cpp
    panels/timeline_panel.cpp
    panels/viewer_panel.cpp
    panels/media_panel.cpp
    
    # Widgets
    widgets/node_graph_widget.cpp
    widgets/node_item.cpp
    widgets/viewer_widget.cpp
    widgets/timeline_widget.cpp
    
    # Theme
    theme/dark_theme.cpp
)

target_include_directories(nuke_ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(nuke_ui PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    nuke_core
)
