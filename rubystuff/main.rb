require 'gtk3'
require 'net/http'
require 'json'
require 'open-uri'


#main Window!

window = Gtk::Window.new
window.set_title("Github Stats Fetcher!")
window.set_default_size(400 , 400)
window.set_border_width(12)
window.signal_connect("destroy"){Gtk.main_quit}

#vertical box layout for arrnging widegets
vbox = Gtk::Box.new(:vertical , 10)
window.add(vbox)

#input field!

user_input = Gtk::Entry.new
user_input.placeholder_text = "Enter github username"
vbox.pack_start(user_input, expand: false, fill: true , padding: 0)

#fetch button
fetch_button =  Gtk::Button.new(label: "fetch stuff")
vbox.pack_start(fetch_button, expand: false , fill: true , padding: 0)

#getting the avatar!
avatar_image = Gtk::Image.new
vbox.pack_start(avatar_image , expand: false , fill: true , padding: 0)

#stats.info.label!
stat_label = Gtk::Label.new
stat_label.set_line_wrap(true)
vbox.pack_start(stat_label, expand: false , fill: true, padding: 0)

# fetch logic(button)
fetch_button.signal_connect("clicked")do
  username = user_input.text.strip

  if username.empty?
    stat_label.text = "enter a username plsh"
    next
  end

  begin
    #Fetch Githjub user data 
    url = URI("https://api.github.com/users/#{username}")
    data = JSON.parse(Net::HTTP.get(url))

    if data["avatar_url"]
      loader = GdkPixbuf::PixbufLoader.new
      loader.write(URI.open(data["avatar_url"]).read)
      loader.close
      avatar_image.pixbuf = loader.pixbuf.scale_simple(100, 100, GdkPixbuf::InterpType::BILINEAR)
    end

    #Display user statttt 

    stat_label.text = <<~INFO
    #{data['login']}
    Followers : #{data['followers']}
    Following : #{data['following']}
    Repos : #{data['public_repos']}
    BIO : #{data['bio'] || 'No bio'}
    INFO

  rescue
   stat_label.text = "failed to fetch data ...Check username or network!"
      
    
  end

end

#show all the widegets
window.show_all
Gtk.main
