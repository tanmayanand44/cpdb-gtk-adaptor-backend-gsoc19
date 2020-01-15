#include "config.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include <cairo-ps.h>
#include <cairo-svg.h>

#include <glib/gi18n-lib.h>

#include "gtk/gtk.h"
#include "gtk/gtkprinterprivate.h"

// #include libraary headers
typedef struct _GtkPrintBackendAdaptorClass GtkPrintBackendAdaptorClass;

#define _STREAM_MAX_CHUNK_SIZE 8192

struct _GtkPrintBackendAdaptorClass
{
  GtkPrintBackendClass parent_class;
};

struct _GtkPrintBackendAdaptor
{
  GtkPrintBackend parent_instance;
};
typedef struct _GtkPrintBackendAdaptor    GtkPrintBackendAdaptor;
// typedef enum
// {
//   FORMAT_PDF,
//   FORMAT_PS,
//   FORMAT_SVG,
//   N_FORMATS
// } OutputFormat;
//
// static const gchar* formats[N_FORMATS] =
// {
//   "pdf",
//   "ps",
//   "svg"
// };
static GObjectClass *backend_parent_class;

static void                 gtk_print_backend_adaptor_class_init      (GtkPrintBackendAdaptorClass *class);
static void                 gtk_print_backend_adaptor_init            (GtkPrintBackendAdaptor      *impl);
static void                 adaptor_printer_get_settings_from_options (GtkPrinter              *printer,
								    GtkPrinterOptionSet     *options,
								    GtkPrintSettings        *settings);
static GtkPrinterOptionSet *adaptor_printer_get_options               (GtkPrinter              *printer,
								    GtkPrintSettings        *settings,
								    GtkPageSetup            *page_setup,
								    GtkPrintCapabilities     capabilities);
static void                 adaptor_printer_prepare_for_print         (GtkPrinter              *printer,
								    GtkPrintJob             *print_job,
								    GtkPrintSettings        *settings,
								    GtkPageSetup            *page_setup);
static void                 gtk_print_backend_adaptor_print_stream    (GtkPrintBackend         *print_backend,
								    GtkPrintJob             *job,
								    GIOChannel              *data_io,
								    GtkPrintJobCompleteFunc  callback,
								    gpointer                 user_data,
								    GDestroyNotify           dnotify);
static cairo_surface_t *    adaptor_printer_create_cairo_surface      (GtkPrinter              *printer,
								    GtkPrintSettings        *settings,
								    gdouble                  width,
								    gdouble                  height,
								    GIOChannel              *cache_io);

static GList *              adaptor_printer_list_papers               (GtkPrinter              *printer);
static GtkPageSetup *       adaptor_printer_get_default_page_size     (GtkPrinter              *printer);




static void
gtk_print_backend_adaptor_class_init (GtkPrintBackendAdaptorClass *class)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    gtk_print_backend_file_class_init(class);
  }
  else //if()// for others
  {

  }
}
static void
gtk_print_backend_adaptor_init (GtkPrintBackendAdaptor *backend)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    gtk_print_backend_file_init(backend);
  }
  else //if()// for others
  {

  }
}

static void
file_printer_get_settings_from_options (GtkPrinter          *printer,
					GtkPrinterOptionSet *options,
					GtkPrintSettings    *settings)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    file_printer_get_settings_from_options(GtkPrinter          *printer,
    					GtkPrinterOptionSet *options,
    					GtkPrintSettings    *settings);
  }
  else //if()// for others
  {

  }
}

static GtkPrinterOptionSet *
adaptor_printer_get_options (GtkPrinter           *printer,
			  GtkPrintSettings     *settings,
			  GtkPageSetup         *page_setup,
			  GtkPrintCapabilities  capabilities)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    return file_printer_get_options(printer,settings,page_setup,capabilities);
  }
  else //if()// for others
  {

  }
}

static void
adaptor_printer_prepare_for_print (GtkPrinter       *printer,
				GtkPrintJob      *print_job,
				GtkPrintSettings *settings,
				GtkPageSetup     *page_setup)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    return file_printer_prepare_for_print(printer,print_job,settings,page_setup);
  }
  else //if()// for others
  {

  }
}

static void
gtk_print_backend_adaptor_print_stream (GtkPrintBackend        *print_backend,
				     GtkPrintJob            *job,
				     GIOChannel             *data_io,
				     GtkPrintJobCompleteFunc callback,
				     gpointer                user_data,
				     GDestroyNotify          dnotify)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    file_printer_prepare_for_print(printer,print_job,settings,page_setup);
  }
  else //if()// for others
  {

  }
}

static cairo_surface_t *
file_printer_create_cairo_surface (GtkPrinter       *printer,
				   GtkPrintSettings *settings,
				   gdouble           width,
				   gdouble           height,
				   GIOChannel       *cache_io)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    return file_printer_create_cairo_surface(printer,settings,width,height,cache_io);
  }
  else //if()// for others
  {

  }
}

static GList *
adaptor_printer_list_papers (GtkPrinter *printer)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    return file_printer_list_papers(printer);
  }
  else //if()// for others
  {

  }
}

static GtkPageSetup *
adaptor_printer_get_default_page_size (GtkPrinter *printer)
{
  if(access( "/usr/local/lib/print-backends/file", F_OK))//file backend present
  {
    return file_printer_get_default_page_size(file_printer_list_papers(printer);
  }
  else //if()// for others
  {

  }
}
