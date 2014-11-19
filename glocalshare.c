/***********
 * cs50 
 * final
 * sujit maharjan
 ***********/
 #include <gtk/gtk.h>
 #include <stdlib.h>

 #define UI_FILE "/usr/share/glocalshare/builder.ui"
 #define ICON "/usr/share/glocalshare/icon.png"
 #define LOCALSHARE "localshare"
#define GETSHARE "getshare"

GtkWidget *window;
GtkWidget *menu_button;
GtkWidget *ui_page[2];
GtkEntry *sharefile;
GtkEntry *getfile;
GtkEntry *shareport;
GtkEntry *getport;
GtkEntry *getip;
GtkLabel *display;
GtkLabel *shareip;
GtkAboutDialog *about_glocalshare;


int pwd(char* path)
{
char cmd[]="pwd";
  FILE *output = popen(cmd,"r");
  while(!feof(output))
    {
      fscanf(output,"%s",path);
  
    }
  pclose(output);
  return 0;   
}
int localip(char* ip)
{
char cmd[]="ip addr | grep 'state UP' -A2 | tail -n1 | awk '{print $2}' | cut -f1 -d'/'";
  FILE *output = popen(cmd,"r");
  while(!feof(output))
    {
      fscanf(output,"%s",ip);
  
    }
  pclose(output);
  return 0;   
}
int run_bash_displaying(char *cmd)
{
  FILE *output = popen(cmd,"r");
  
  while(!feof(output))
    {
      char c;
      c=fgetc(output);
      putchar(c);
      char line[255]="";
      int no=0;
      if (c != NULL && no < 255)
	{
	  line[no++] = c;
	  if (c == '\n')
	    {
	      line[no++] = '\0';
	      putchar(c);
	      no = 0;
	      line[0] ="";
	    }


	}
      
    }
  
  pclose(output);
  return 0;   
}
void
runlocalshare (GtkButton *button,
                gpointer   user_data)
{
  const char* file_name = gtk_entry_get_text(sharefile);
  const char* port =  gtk_entry_get_text(shareport);
  char path[100];
  pwd(path);
  char cmd[400];
  sprintf(cmd,"pkexec bash %s %s %s",LOCALSHARE,file_name,port);
  g_print(cmd);
  int pid = fork();
  if( pid == -1)
    {
      g_print("errro in fork");
    }
  else if (pid == 0)
    {
      run_bash_displaying(cmd);
      _exit(0);
    }
  else
    return;
  

}
void
rungetshare (GtkButton *button,
                gpointer   user_data)
{

  const char* file_name = gtk_entry_get_text(getfile);
  const char* port =  gtk_entry_get_text(getport);
  const char* ip = gtk_entry_get_text(getip);
 
  char cmd[400];
  sprintf(cmd,"pkexec bash %s %s %s %s",GETSHARE,ip,port,file_name);
  g_print(cmd);
  int pid = fork();
  if( pid == -1)
    {
      g_print("errro in fork");
    }
  else if (pid == 0)
    {
      run_bash_displaying(cmd);
      _exit(0);
    }
  else
    return;
  
 
}

static void
quit (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       app)
{
  g_application_quit (G_APPLICATION (app));
}
static void
about (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       user_data)
{
  
  
  const gchar *authors[] = {
    "Sujit Maharjan"
    
  };

  

  gtk_show_about_dialog (GTK_WINDOW (window),
                         "program-name", "Glocalshare",
			 "logo",NULL,
			 "logo-icon-name","shubhajeet creation",
			 "comments","Transfare a file in local network",
                         "version","1", 
                         "copyright", "(C) 1997-2009 shubhajeet aka Sujit Maharjan",
                         "license-type", GTK_LICENSE_LGPL_2_1,
                         "website", "http://www.maharjansujit.com.np",
                         "comments", "Program to share files locally.",
                         "authors", authors,
			 "documenters",NULL,
                         "title", "About Glocalshare",
                         NULL);
 
}


static void
startup (GtkApplication *app,
	 gpointer user_data)
{
 GMenu *menu;
 GSimpleAction *quit_action;
 GSimpleAction *about_action;
  /* Initialize the GMenu, and add a menu item with label "About" and action 
   * "win.about". Also add another menu item with label "Quit" and action 
   * "app.quit" 
   */
  menu = g_menu_new ();
  g_menu_append (menu, "About", "app.about");
  g_menu_append (menu, "Quit", "app.quit");

  /* Create a new simple action for the application. (In this case it is the 
   * "quit" action.
   */
  quit_action = g_simple_action_new ("quit", NULL);

  /* Ensure that the menu we have just created is set for the overall application */
  gtk_application_set_app_menu (GTK_APPLICATION (app), G_MENU_MODEL (menu));

  g_signal_connect (quit_action, 
                    "activate", 
                    G_CALLBACK (quit), 
                    app);

  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (quit_action));
  about_action = g_simple_action_new ("about", NULL); 
  g_signal_connect (about_action, "activate", G_CALLBACK (about), 
                    NULL);
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (about_action));
}
static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GError* error = NULL;
  GtkBuilder *builder;
  
  gchar ip[20]="";
  localip(ip);
  
  builder = gtk_builder_new ();
  
 
  if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
    {
      g_critical ("Couldn't load builder file: %s", error->message);
      g_error_free (error);
    }
  
  window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
  
  
  gtk_builder_connect_signals(builder,app);
  sharefile = GTK_ENTRY(gtk_builder_get_object(builder,"share_file"));
  getfile = GTK_ENTRY(gtk_builder_get_object(builder,"get_file"));
  shareport = GTK_ENTRY(gtk_builder_get_object (builder, "share_port_no"));
  getport = GTK_ENTRY(gtk_builder_get_object (builder, "get_port_no"));
  getip = GTK_ENTRY(gtk_builder_get_object (builder, "get_ip"));  
  shareip = GTK_LABEL(gtk_builder_get_object (builder, "share_ip"));
  
  
  gtk_label_set_text(shareip,ip);
  

  //  GMenu *menu = G_MENU (gtk_builder_get_object (builder,"menubar"));
  
  gtk_window_set_default_icon_from_file( ICON ,&error);
  

  gtk_widget_show_all (window);
  gtk_application_add_window(app,GTK_WINDOW (window) );
  
}

int
main (int argc, char **argv)
{

  GtkApplication *app;
  int status;


  app = gtk_application_new ("org.gtk.glocalshare", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "startup", G_CALLBACK (startup), NULL);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);  

  status = g_application_run (G_APPLICATION (app), argc, argv);

  g_object_unref (app);
  return status;
}
