
#include <gtk/gtk.h>

static void popdialog(GtkWidget *widget, gpointer   data)
{
	GtkWidget *dialog, *label, *okay_button;

	/* Create the widgets */

	dialog = gtk_dialog_new();
	gtk_window_set_title (GTK_WINDOW (dialog), "new dialog");
	label = gtk_label_new ("Dialog Window");
	okay_button = gtk_button_new_with_label("Okay");

	/* Ensure that the dialog box is destroyed when the user clicks ok. */

	gtk_signal_connect_object (GTK_OBJECT (okay_button), "clicked",
			GTK_SIGNAL_FUNC (gtk_widget_destroy), dialog);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->action_area),
			okay_button);

	/* Add the label, and show everything we've added to the dialog. */

	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
			label);
	gtk_widget_show_all (dialog);   
}

/* Create a new hbox with an image and a label packed into it
 * and return the box. */
static GtkWidget *xpm_label_box( gchar     *xpm_filename,
		gchar     *label_text )
{
	GtkWidget *box;
	GtkWidget *label;
	GtkWidget *image;

	/* Create box for image and label */
	box = gtk_hbox_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);

	/* Now on to the image stuff */
	image = gtk_image_new_from_file (xpm_filename);

	/* Create a label for the button */
	label = gtk_label_new (label_text);

	/* Pack the image and label into the box */
	gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
	gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

	gtk_widget_show (image);
	gtk_widget_show (label);

	return box;
}

static void destroy( GtkWidget *widget, gpointer   data )
{
	    gtk_main_quit ();
}

/* Create a Button Box with the specified parameters */
static GtkWidget *create_bbox(
		gint  spacing,
		gint  child_w,
		gint  child_h,
		gint  layout )
{
	GtkWidget *frame;
	GtkWidget *bbox;
	GtkWidget *button;

	bbox = gtk_vbutton_box_new ();

	/* Set the appearance of the Button Box */
	gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), layout);
	gtk_box_set_spacing (GTK_BOX (bbox), spacing);

	button = gtk_button_new_from_stock (GTK_STOCK_OK);
	gtk_container_add (GTK_CONTAINER (bbox), button);

	gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			G_CALLBACK(destroy), NULL);

	button = gtk_check_button_new_with_label("Check Button");
	gtk_container_add (GTK_CONTAINER (bbox), button);

	button = gtk_button_new_from_stock (GTK_STOCK_HELP);
	gtk_container_add (GTK_CONTAINER (bbox), button);

	g_signal_connect (button, "clicked", G_CALLBACK (popdialog), NULL);

	return bbox;
}

int main(int argc, char *argv[])
{
	static GtkWidget* window = NULL;
	GtkWidget *hbox;
	GtkWidget *bbox;
	GtkWidget *xpmbox;
	GtkWidget *button;

	/* Initialize GTK */
	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Button Boxes");

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), hbox);

	gtk_box_pack_start (GTK_BOX (hbox),
			create_bbox (5, 85, 20, GTK_BUTTONBOX_SPREAD),
			TRUE, TRUE, 0);

	bbox = gtk_vbutton_box_new ();
	gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), GTK_BUTTONBOX_SPREAD);
	gtk_box_set_spacing (GTK_BOX (bbox), 20);

    gtk_container_add (GTK_CONTAINER (hbox), bbox);

    button = gtk_button_new ();
    gtk_container_add (GTK_CONTAINER (hbox), button);
	gtk_container_set_border_width (GTK_CONTAINER (button), 30);

    xpmbox = xpm_label_box ("info.xpm", "cool button");
    gtk_container_add (GTK_CONTAINER (button), xpmbox);

	gtk_widget_show_all (window);

	/* Enter the event loop */
	gtk_main ();

	return 0;
}

