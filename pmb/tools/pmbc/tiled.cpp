#include "./tiled.hpp"


auto pmbc::err_to_str(pmbc::tiled_tileset_error err)
    -> const char*
{
    // FIXME: Return better messages
    switch (err) {
    case pmbc::tiled_tileset_error::wrong_type:
        return "pmbc::tiled_tileset_error::wrong_type";
    case pmbc::tiled_tileset_error::missing_name:
        return "pmbc::tiled_tileset_error::missing_name";
    case pmbc::tiled_tileset_error::missing_image:
        return "pmbc::tiled_tileset_error::missing_image";
    case pmbc::tiled_tileset_error::missing_columns:
        return "pmbc::tiled_tileset_error::missing_columns";
    case pmbc::tiled_tileset_error::missing_imageheight:
        return "pmbc::tiled_tileset_error::missing_imageheight";
    case pmbc::tiled_tileset_error::missing_imagewidth:
        return "pmbc::tiled_tileset_error::missing_imagewidth";
    case pmbc::tiled_tileset_error::missing_margin:
        return "pmbc::tiled_tileset_error::missing_margin";
    case pmbc::tiled_tileset_error::missing_spacing:
        return "pmbc::tiled_tileset_error::missing_spacing";
    case pmbc::tiled_tileset_error::missing_tilecount:
        return "pmbc::tiled_tileset_error::missing_tilecount";
    case pmbc::tiled_tileset_error::missing_tileheight:
        return "pmbc::tiled_tileset_error::missing_tileheight";
    case pmbc::tiled_tileset_error::missing_tilewidth:
        return "pmbc::tiled_tileset_error::missing_tilewidth";
    }
    return "<unknown value>";
}


auto pmbc::read_tiled_tileset(const nlohmann::json& tiled_json)
    -> cmm::result<pmbc::tiled_tileset, pmbc::tiled_tileset_error>
{
    auto type = tiled_json.find("type");
    if (type == tiled_json.end()
        or not type->is_string()
        or not (type->get<std::string>() == "tileset"))
        return cmm::err(pmbc::tiled_tileset_error::wrong_type);

    auto name = tiled_json.find("name");
    if (name == tiled_json.end() or not name->is_string())
        return cmm::err(pmbc::tiled_tileset_error::missing_name);

    auto image = tiled_json.find("image");
    if (image == tiled_json.end() or not image->is_string())
        return cmm::err(pmbc::tiled_tileset_error::missing_image);

    auto columns = tiled_json.find("columns");
    if (columns == tiled_json.end() or not columns->is_number())
        return cmm::err(pmbc::tiled_tileset_error::missing_columns);

    auto imageheight = tiled_json.find("imageheight");
    if (imageheight == tiled_json.end() or not imageheight->is_number())
        return cmm::err(pmbc::tiled_tileset_error::missing_imageheight);

    auto imagewidth = tiled_json.find("imagewidth");
    if (imagewidth == tiled_json.end() or not imagewidth->is_number())
        return cmm::err(pmbc::tiled_tileset_error::missing_imagewidth);

    auto margin = tiled_json.find("margin");
    if (margin == tiled_json.end() or not margin->is_number())
        return cmm::err(pmbc::tiled_tileset_error::missing_margin);

    auto spacing = tiled_json.find("spacing");
    if (spacing == tiled_json.end() or not spacing->is_number())
        return cmm::err(pmbc::tiled_tileset_error::missing_spacing);

    auto tilecount = tiled_json.find("tilecount");
    if (tilecount == tiled_json.end() or not tilecount->is_number())
        return cmm::err(pmbc::tiled_tileset_error::missing_tilecount);

    auto tileheight = tiled_json.find("tileheight");
    if (tileheight == tiled_json.end() or not tileheight->is_number())
        return cmm::err(pmbc::tiled_tileset_error::missing_tileheight);

    auto tilewidth = tiled_json.find("tilewidth");
    if (tilewidth == tiled_json.end() or not tilewidth->is_number())
        return cmm::err(pmbc::tiled_tileset_error::missing_tilewidth);

    pmbc::tiled_tileset ts;

    ts.type        = type->get<std::string>();
    ts.name        = name->get<std::string>();
    ts.image       = image->get<std::string>();
    ts.columns     = columns->get<int>();
    ts.imageheight = imageheight->get<int>();
    ts.imagewidth  = imagewidth->get<int>();
    ts.margin      = margin->get<int>();
    ts.spacing     = spacing->get<int>();
    ts.tilecount   = tilecount->get<int>();
    ts.tileheight  = tileheight->get<int>();
    ts.tilewidth   = tilewidth->get<int>();

    return cmm::ok(ts);
}
