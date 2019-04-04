'use strict';

const mod = GE.Modules();
mod.require("SDL");
mod.require("Resource");

const init_flags = SDL.InitFlags();
const window_flags = SDL.WindowFlags();
const render_flags = SDL.RenderFlags();
const pixel_format = SDL.Pixelformat();
const texture_access = SDL.TextureAccess();

const dir = Resource.Directory("res");
const tileset_reference = Resource.Reference(dir);
tileset_reference.Find("res:examples:tmw_desert_spacing.png");
const cat_reference = Resource.Reference(dir);
cat_reference.Find("res:images:cat.bmp");

const ttf_reference = Resource.Reference(dir);
ttf_reference.Find("res:ttf-bitstream-vera-1.10:VeraMono.ttf")

const VeraMono = SDL.TTF(ttf_reference, 36);

const desert_tilemap_reference = Resource.Reference(dir);
desert_tilemap_reference.Find("res:examples:desert.tmx");
const desert_tilemap = Resource.Tilemap(desert_tilemap_reference);

const desert_tile_layer_surface = Resource.TileLayerSurface("Ground", desert_tilemap);
desert_tile_layer_surface.CreateRGBSurfaceWithFormat(0,640,480,32,pixel_format.SDL_PIXELFORMAT_ARGB8888);
SDL.Init(init_flags.SDL_INIT_VIDEO);
const win = SDL.Window("howdy", 100, 100, 640, 480, window_flags.SDL_WINDOW_SHOWN);
// const ren = SDL.Renderer(win, -1, render_flags.SDL_RENDERER_ACCELERATED | render_flags.SDL_RENDERER_PRESENTVSYNC);
const ren = SDL.Renderer(win, -1, render_flags.SDL_RENDERER_ACCELERATED );

const surface = Resource.TileSetSurface("Desert", desert_tilemap);
const surface2 = SDL.Surface();
desert_tile_layer_surface.AddTileSet(surface);
desert_tile_layer_surface.UpdateSurface();


surface2.CreateSurfaceFromResource(cat_reference);
surface2.ReformatForWindow(win);

const text_surface = SDL.Surface();

desert_tile_layer_surface.ReformatForWindow(win);

desert_tile_layer_surface.SetSurfaceAlphaMod(200);

const texture = SDL.Texture();
texture.CreateTextureFromSurface(ren,surface2);

texture.Update(surface2);

const event = SDL.Event();

let should_quit = false;

do {
    if ( event.PollEvent() ) {
        if (event.Type() == event.SDL_QUIT) {
            should_quit = true;
        }
    }

    text_surface.CreateTTFSurface(VeraMono, String(ren.PerformanceCounter));
    surface2.BlitSurface(desert_tile_layer_surface);
    surface2.BlitSurface(text_surface);
    texture.Update(surface2);

    ren.Clear();
    ren.Copy(texture);
    ren.PresentPerformance();

//     print(ren.PerformanceCounter);
} while(should_quit == false );

