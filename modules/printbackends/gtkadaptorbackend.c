#include "config.h"

#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <cpdb-libs-frontend.h>
#include <errno.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include <cairo-ps.h>
#include <cairo-svg.h>

#include <glib/gstdio.h>
#include <glib/gi18n-lib.h>
#include <gmodule.h>

#include <gtk/gtk.h>
#include <gtk/gtkprintbackend.h>
#include <gtk/gtkunixprint.h>
#include <gtk/gtkprinter-private.h>

#include "gtkprintbackendcpdb.h"

#include <gtkprintutils.h>

typedef struct _GtkPrintBackendCpdbClass GtkPrintBackendCpdbClass;

#define GTK_PRINT_BACKEND_CPDB_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_PRINT_BACKEND_CPDB, GtkPrintBackendCpdbClass))
#define GTK_IS_PRINT_BACKEND_FILE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_PRINT_BACKEND_CPDB))
#define GTK_PRINT_BACKEND_CPDB_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_PRINT_BACKEND_CPDB, GtkPrintBackendCpdbClass))

#define _STREAM_MAX_CHUNK_SIZE 8192

static GType print_backent_cpdb_type = 0;
struct _GtkPrintBackendCpdbClass
{
  GtkPrintBackendClass parent_class;
};

struct _GtkPrintBackendCpdb
{
  GtkPrintBackend parent_instance;
  FrontendObj *f;
}

static GObjectClass *backend_parent_class;

static GtkPrinter *
find_printer_by_uuid (GtkPrintBackendCups *backend,
                      const gchar         *UUID)
{
  GtkPrinterCups *printer;
  GtkPrinter     *result = NULL;
  GList          *printers;
  GList          *iter;
  gchar          *printer_uuid;

  printers = gtk_print_backend_get_printer_list (GTK_PRINT_BACKEND (backend));
  for (iter = printers; iter != NULL; iter = iter->next)
    {
      printer = GTK_PRINTER_CUPS (iter->data);
      if (printer->original_device_uri != NULL)
        {
          printer_uuid = g_strrstr (printer->original_device_uri, "uuid=");
          if (printer_uuid != NULL && strlen (printer_uuid) >= 41)
            {
              printer_uuid += 5;
              printer_uuid = g_strndup (printer_uuid, 36);

              if (g_uuid_string_is_valid (printer_uuid))
                {
                  if (g_strcmp0 (printer_uuid, UUID) == 0)
                    {
                      result = GTK_PRINTER (printer);
                      g_free (printer_uuid);
                      break;
                    }
                }

              g_free (printer_uuid);
            }
        }
    }

  g_list_free (printers);

  return result;
}


static gchar *
output_file_from_settings (GtkPrintSettings *settings,
			   const gchar      *default_format)
{
  gchar *uri = NULL;

  if (settings)
    uri = g_strdup (gtk_print_settings_get (settings, GTK_PRINT_SETTINGS_OUTPUT_URI));

  if (uri == NULL)
    {
      const gchar *extension, *basename = NULL, *output_dir = NULL;
      gchar *name, *locale_name, *path;

      if (default_format)
        extension = default_format;
      else
        {
          OutputFormat format;

          format = format_from_settings (settings);
          switch (format)
            {
              default:
              case FORMAT_PDF:
                extension = "pdf";
                break;
              case FORMAT_PS:
                extension = "ps";
                break;
              case FORMAT_SVG:
                extension = "svg";
                break;
            }
        }

      if (settings)
        basename = gtk_print_settings_get (settings, GTK_PRINT_SETTINGS_OUTPUT_BASENAME);
      if (basename == NULL)
        basename = _("output");

      name = g_strconcat (basename, ".", extension, NULL);

      locale_name = g_filename_from_utf8 (name, -1, NULL, NULL, NULL);
      g_free (name);

      if (locale_name != NULL)
        {
          if (settings)
            output_dir = gtk_print_settings_get (settings, GTK_PRINT_SETTINGS_OUTPUT_DIR);
          if (output_dir == NULL)
            {
              const gchar *document_dir = g_get_user_special_dir (G_USER_DIRECTORY_DOCUMENTS);

              if (document_dir == NULL)
                {
                  gchar *current_dir = g_get_current_dir ();
                  path = g_build_filename (current_dir, locale_name, NULL);
                  g_free (current_dir);
                }
              else
                path = g_build_filename (document_dir, locale_name, NULL);

              uri = g_filename_to_uri (path, NULL, NULL);
	    }
          else
            {
              path = g_build_filename (output_dir, locale_name, NULL);
              uri = g_filename_to_uri (path, NULL, NULL);
            }

          g_free (path);
          g_free (locale_name);
        }
    }

  return uri;
}
