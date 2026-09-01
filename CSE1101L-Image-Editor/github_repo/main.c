
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iup.h>

#include "image.h"
#include "processing.h"


static Image* current_image  = NULL;  
static Image* previous_image = NULL;   


static Ihandle* bright_text = NULL;
static Ihandle* crop_x = NULL, *crop_y = NULL, *crop_w = NULL, *crop_h = NULL;
static Ihandle* status_label = NULL;


static Ihandle* view_dlg   = NULL;  
static Ihandle* view_label = NULL;  
static Ihandle* view_img   = NULL;  
static int view_w = 0, view_h = 0;  

static int cb_viewer_close(Ihandle* dlg)
{
    IupHide(dlg);
    return IUP_IGNORE;   
}

static void update_display(void)
{
    char size[32], msg[64], pos[32];
    Ihandle* new_img;
    int x, y;

    if (!current_image) {
        if (status_label)
            IupSetAttribute(status_label, "TITLE", "no image loaded");
        if (view_dlg)
            IupHide(view_dlg);
        return;
    }

    fprintf(stderr, "[display] showing %dx%d image\n",
            current_image->width, current_image->height);
    snprintf(msg, sizeof(msg), "image: %dx%d",
             current_image->width, current_image->height);
    if (status_label)
        IupSetAttribute(status_label, "TITLE", msg);

    new_img = IupImageRGB(current_image->width, current_image->height,
                          (unsigned char*)current_image->data);
    if (!new_img) {
        fprintf(stderr, "[display] IupImageRGB failed\n");
        return;
    }

    if (!view_dlg) {
        view_label = IupLabel(NULL);
        IupSetAttributeHandle(view_label, "IMAGE", new_img);
        view_w = current_image->width;
        view_h = current_image->height;
        snprintf(size, sizeof(size), "%dx%d", view_w, view_h);
        IupSetAttribute(view_label, "RASTERSIZE", size);

        view_dlg = IupDialog(view_label);
        IupSetAttribute(view_dlg, "TITLE", "Image Viewer");
        IupSetCallback(view_dlg, "CLOSE_CB", cb_viewer_close);
        IupShowXY(view_dlg, IUP_LEFT, IUP_TOP);
        fprintf(stderr, "[display] viewer CREATED %dx%d\n", view_w, view_h);
    } else {
        x = IupGetInt(view_dlg, "X");
        y = IupGetInt(view_dlg, "Y");

        IupSetAttributeHandle(view_label, "IMAGE", new_img);

        if (view_w != current_image->width || view_h != current_image->height) {
            view_w = current_image->width;
            view_h = current_image->height;
            snprintf(size, sizeof(size), "%dx%d", view_w, view_h);
            IupSetAttribute(view_label, "RASTERSIZE", size);
            IupRefresh(view_label);
            IupRefresh(view_dlg);
            IupRedraw(view_label, 0);
            fprintf(stderr, "[display] updated + RESIZED to %dx%d\n", view_w, view_h);
        } else {
            IupRedraw(view_label, 0);
            fprintf(stderr, "[display] updated IN PLACE (same size)\n");
        }

        {
            const char* vis = IupGetAttribute(view_dlg, "VISIBLE");
            if (!vis || strcmp(vis, "YES") != 0)
                IupShow(view_dlg);
        }

        if (x >= 0 && y >= 0 &&
            (IupGetInt(view_dlg, "X") != x || IupGetInt(view_dlg, "Y") != y)) {
            snprintf(pos, sizeof(pos), "%d,%d", x, y);
            IupSetAttribute(view_dlg, "POSITION", pos);
            fprintf(stderr, "[display] position restored to %d,%d\n", x, y);
        }
    }

    if (view_img)
        IupDestroy(view_img);
    view_img = new_img;
}


static int have_image(void)
{
    if (!current_image) {
        IupMessage("Error", "No image is loaded.\nUse File > Open first.");
        return 0;
    }
    return 1;
}

static int save_undo_copy(void)
{
    Image* copy = copy_image(current_image);
    if (!copy) {
        IupMessage("Error", "Out of memory while saving the undo copy.");
        return 0;
    }
    free_image(previous_image);
    previous_image = copy;
    return 1;
}

static int text_to_int(Ihandle* text, int* out)
{
    const char* s = IupGetAttribute(text, "VALUE");
    char* end;
    long v;

    if (!s || *s == '\0')
        return 0;
    v = strtol(s, &end, 10);
    if (end == s || *end != '\0')
        return 0;
    *out = (int)v;
    return 1;
}

/* menu callbacks */

static int cb_open(Ihandle* ih)
{
    Ihandle* dlg;
    const char* path;
    Image* img;

    (void)ih;
    dlg = IupFileDlg();
    IupSetAttribute(dlg, "DIALOGTYPE", "OPEN");
    IupSetAttribute(dlg, "EXTFILTER", "Bitmap files (*.bmp)|*.bmp|");
    IupPopup(dlg, IUP_CENTER, IUP_CENTER);

    if (IupGetInt(dlg, "STATUS") == -1) {     /* -1 = cancelled, 1 = opened */
        IupDestroy(dlg);
        return IUP_DEFAULT;
    }

    path = IupGetAttribute(dlg, "VALUE");
    img = (path && *path) ? load_image(path) : NULL;
    IupDestroy(dlg);

    if (!img) {
        IupMessage("Error", "Could not load this file.\nIt must be a valid BMP image.");
        return IUP_DEFAULT;
    }

    free_image(previous_image);
    previous_image = current_image;
    current_image  = img;

    update_display();
    return IUP_DEFAULT;
}

static int cb_save(Ihandle* ih)
{
    Ihandle* dlg;
    const char* path;
    int ok;

    (void)ih;
    if (!have_image())
        return IUP_DEFAULT;

    dlg = IupFileDlg();
    IupSetAttribute(dlg, "DIALOGTYPE", "SAVE");
    IupSetAttribute(dlg, "EXTFILTER", "Bitmap files (*.bmp)|*.bmp|");
    IupPopup(dlg, IUP_CENTER, IUP_CENTER);

    if (IupGetInt(dlg, "STATUS") == -1) {
        IupDestroy(dlg);
        return IUP_DEFAULT;
    }

    path = IupGetAttribute(dlg, "VALUE");
    ok = (path && *path) && save_image(path, current_image);
    IupDestroy(dlg);

    if (!ok)
        IupMessage("Error", "Could not save the file.");
    return IUP_DEFAULT;
}

static int cb_exit(Ihandle* ih)
{
    (void)ih;
    return IUP_CLOSE;
}

/* operations to modify */

static int cb_grayscale(Ihandle* ih) { (void)ih;
    if (!have_image() || !save_undo_copy()) return IUP_DEFAULT;
    grayscale(current_image);
    update_display();
    return IUP_DEFAULT;
}

static int cb_invert(Ihandle* ih) { (void)ih;
    if (!have_image() || !save_undo_copy()) return IUP_DEFAULT;
    invert(current_image);
    update_display();
    return IUP_DEFAULT;
}

static int cb_hflip(Ihandle* ih) { (void)ih;
    if (!have_image() || !save_undo_copy()) return IUP_DEFAULT;
    hflip(current_image);
    update_display();
    return IUP_DEFAULT;
}

static int cb_vflip(Ihandle* ih) { (void)ih;
    if (!have_image() || !save_undo_copy()) return IUP_DEFAULT;
    vflip(current_image);
    update_display();
    return IUP_DEFAULT;
}

static int cb_brightness(Ihandle* ih)
{
    int value;

    (void)ih;
    if (!have_image())
        return IUP_DEFAULT;

    if (!text_to_int(bright_text, &value) || value < -255 || value > 255) {
        IupMessage("Error", "Brightness must be a whole number between -255 and 255.");
        return IUP_DEFAULT;
    }

    if (!save_undo_copy()) return IUP_DEFAULT;
    brightness(current_image, value);
    update_display();
    return IUP_DEFAULT;
}

/*  operations to build  */

static int cb_rotate(Ihandle* ih)
{
    Image* result;
    (void)ih;
    if (!have_image()) return IUP_DEFAULT;

    result = rotate90(current_image);
    if (!result) {
        IupMessage("Error", "Rotation failed (out of memory?).");
        return IUP_DEFAULT;
    }
    free_image(previous_image);
    previous_image = current_image;
    current_image  = result;
    update_display();
    return IUP_DEFAULT;
}

static int cb_blur(Ihandle* ih)
{
    Image* result;
    (void)ih;
    if (!have_image()) return IUP_DEFAULT;

    result = blur(current_image);
    if (!result) {
        IupMessage("Error", "Blur failed (out of memory?).");
        return IUP_DEFAULT;
    }
    free_image(previous_image);
    previous_image = current_image;
    current_image  = result;
    update_display();
    return IUP_DEFAULT;
}

static int cb_sharpen(Ihandle* ih)
{
    Image* result;
    (void)ih;
    if (!have_image()) return IUP_DEFAULT;

    result = sharpen(current_image);
    if (!result) {
        IupMessage("Error", "Sharpen failed (out of memory?).");
        return IUP_DEFAULT;
    }
    free_image(previous_image);
    previous_image = current_image;
    current_image  = result;
    update_display();
    return IUP_DEFAULT;
}

static int cb_crop(Ihandle* ih)
{
    int x, y, w, h;
    Image* result;
    (void)ih;
    if (!have_image()) return IUP_DEFAULT;

    if (!text_to_int(crop_x, &x) || !text_to_int(crop_y, &y) ||
        !text_to_int(crop_w, &w) || !text_to_int(crop_h, &h)) {
        IupMessage("Error", "Crop values must be whole numbers.");
        return IUP_DEFAULT;
    }

    result = crop(current_image, x, y, w, h);
    if (!result) {
        IupMessage("Error", "Invalid crop region (or out of memory).\n"
                            "Width and height must be > 0 and the region\n"
                            "must fit inside the image.");
        return IUP_DEFAULT;
    }
    free_image(previous_image);
    previous_image = current_image;
    current_image  = result;
    update_display();
    return IUP_DEFAULT;
}

static int cb_undo(Ihandle* ih)
{
    Image* tmp;
    (void)ih;
    if (!previous_image) {
        IupMessage("Info", "Nothing to undo.");
        return IUP_DEFAULT;
    }
    tmp            = current_image;      
    current_image  = previous_image;
    previous_image = tmp;
    update_display();
    return IUP_DEFAULT;
}

/* control panel  */

static Ihandle* make_button(const char* title, Icallback cb)
{
    Ihandle* b = IupButton(title, NULL);
    IupSetCallback(b, "ACTION", cb);
    return b;
}

static void build_gui(void)
{
    Ihandle *mi_open, *mi_save, *mi_exit, *menu;
    Ihandle *toolbar, *bright_row, *crop_row, *vbox, *dlg;

    mi_open = IupItem("Open...", "Ctrl+O");
    mi_save = IupItem("Save...", "Ctrl+S");
    mi_exit = IupItem("Exit",    "Ctrl+Q");
    IupSetCallback(mi_open, "ACTION", cb_open);
    IupSetCallback(mi_save, "ACTION", cb_save);
    IupSetCallback(mi_exit, "ACTION", cb_exit);
    menu = IupMenu(IupSubmenu("File", IupMenu(mi_open, mi_save, mi_exit, NULL)), NULL);

    toolbar = IupHbox(
        make_button("Grayscale", cb_grayscale),
        make_button("Invert",    cb_invert),
        make_button("H-Flip",    cb_hflip),
        make_button("V-Flip",    cb_vflip),
        make_button("Rotate 90", cb_rotate),
        make_button("Blur",      cb_blur),
        make_button("Sharpen",   cb_sharpen),
        make_button("Undo",      cb_undo),
        NULL);

    bright_text = IupText(NULL);
    IupSetAttribute(bright_text, "VALUE", "30");
    IupSetAttribute(bright_text, "RASTERSIZE", "40x");
    bright_row = IupHbox(IupLabel("Brightness:"), bright_text,
                         make_button("Apply", cb_brightness), NULL);

    crop_x = IupText(NULL); IupSetAttribute(crop_x, "VALUE", "0");
    crop_y = IupText(NULL); IupSetAttribute(crop_y, "VALUE", "0");
    crop_w = IupText(NULL); IupSetAttribute(crop_w, "VALUE", "100");
    crop_h = IupText(NULL); IupSetAttribute(crop_h, "VALUE", "100");
    IupSetAttribute(crop_x, "RASTERSIZE", "40x");
    IupSetAttribute(crop_y, "RASTERSIZE", "40x");
    IupSetAttribute(crop_w, "RASTERSIZE", "40x");
    IupSetAttribute(crop_h, "RASTERSIZE", "40x");
    crop_row = IupHbox(
        IupLabel("Crop  x:"), crop_x,
        IupLabel("y:"),       crop_y,
        IupLabel("w:"),       crop_w,
        IupLabel("h:"),       crop_h,
        make_button("Crop", cb_crop),
        NULL);

    status_label = IupLabel("no image loaded");
    IupSetAttribute(status_label, "RASTERSIZE", "140x");

    vbox = IupVbox(toolbar, bright_row, crop_row, status_label, NULL);
    IupSetAttribute(vbox, "MARGIN", "8x8");
    IupSetAttribute(vbox, "GAP", "4");

    dlg = IupDialog(vbox);
    IupSetAttributeHandle(dlg, "MENU", menu);
    IupSetAttribute(dlg, "TITLE", "CSE1101L Image Editor");
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
}

int main(int argc, char* argv[])
{

    setenv("GDK_BACKEND", "x11", 1);

    if (IupOpen(&argc, &argv) == IUP_ERROR) {
        fprintf(stderr, "Error opening IUP.\n");
        return 1;
    }

    build_gui();
    IupMainLoop();

    if (view_img) IupDestroy(view_img);
    free_image(current_image);
    free_image(previous_image);
    IupClose();
    return 0;
}
