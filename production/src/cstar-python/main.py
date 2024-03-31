# CSTAR main python app to be run to connect to the ESP32 over Bluetooth, then send and receive dataimport serial
import serial
import serial.tools.list_ports
# Basic UI libraries (we keeping things simple here)
import customtkinter as ctk
from tkinter import ttk
import multiprocessing
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib import colors
import numpy as np

# our classes and functions
from bluetooth import CstarBluetooth
from audio_processor import AudioProcessor

# please do not read this code its so shitty and im embarrased - Kaden

# Function to list all bluetooth devices available
def list_bluetooth_devices():
    devices = serial.tools.list_ports.comports()
    # get all the devices names and ports in a tuple
    device_names = [device.device for device in devices]
    return device_names

def processes_init(com_port):
    # bluetooth comms object
    blt_obj = CstarBluetooth(com_port, command_queue, audio_pos_queue)
    bluetooth_process = multiprocessing.Process(target=loop_wrapper, args=(blt_obj,))
    bluetooth_process.start()
    processes.append(bluetooth_process)

    # audio processing object
    audio_processor_obj = AudioProcessor(audio_pos_queue, bool_audio_pos_queue, fft_plot_queue)
    audio_processor_process = multiprocessing.Process(target=loop_wrapper, args=(audio_processor_obj,))
    audio_processor_process.start()
    processes.append(audio_processor_process)
    pass

#create a connect button
def connect_to_com_port():
    com_port = com_port_cb.get()# get comport string from bombobox
    try:
        # create a new process to run the main function of each necessary class
        processes_init(com_port)
        # get rid of combobox and button, replace with label that says connected to comport
        com_port_cb.grid_forget()
        connect_btn.grid_forget()
        com_port_label.grid_forget()

        connected_label = ctk.CTkLabel(app, text=f"Connected to {com_port}").grid(row = 0, column = 0, pady=PADY, padx = PADX)

    except serial.SerialException as e:
        print(f"Failed to connect to {com_port}")
        return
    
#simple wrapper to call main, we couldve done this with a lambda lol
def loop_wrapper(obj):
    obj.main()

def send_command():
    # basically add whatever is in the entry to the queue
    command = send_command_entry.get()
    command_queue.put(command)
    # clear the entry
    send_command_entry.delete(0, "end")


if __name__ == "__main__":
        
    processes = []

    # create a multiprocessing queue to put the commands/audio data into
    command_queue = multiprocessing.Queue()
    audio_pos_queue = multiprocessing.Queue() # will contain tuples of position and audio data
    bool_audio_pos_queue = multiprocessing.Queue() # will contain tuples of (bool, audio data, position)
    fft_plot_queue = multiprocessing.Queue() # will contain matplotlib plots of the FFT

    
    # set default padx for all widgets
    PADX = 10
    PADY = 10

    # Initialize the customtkinter app
    ctk.set_appearance_mode("Dark")  # Can be "System", "Dark", or "Light"
    app = ctk.CTk()

    app.title("COM Port Selector")
    app.geometry("1000x600")

    # Create a Label
    com_port_label = ctk.CTkLabel(app, text="Select a COM Port:")
    com_port_label.grid(row=0, column = 0, pady=PADY, padx = PADX)

    # Create a Combobox for COM ports selection
    com_port_cb = ctk.CTkComboBox(app, values=list_bluetooth_devices())
    com_port_cb.grid(row = 1, column = 0)
    com_port_cb.bind("<<ComboboxSelected>>")

    #render then button
    connect_btn = ctk.CTkButton(app, text="Connect", command=connect_to_com_port)
    connect_btn.grid(row = 2, column = 0, pady=PADY, padx = PADX)

    #create text entry for sending data
    send_command_entry = ctk.CTkEntry(app)
    send_command_entry.grid(row = 1, column = 2, pady=PADY, padx = PADX)

    #create a button to send data
    send_command_btn = ctk.CTkButton(app, text="Send Command")
    send_command_btn.grid(row = 2, column = 2, pady=PADY, padx = PADX)

    # bind button to send command
    send_command_btn.bind("<Button-1>", lambda event: send_command())


    #create a blank matplotlib plot
    fig = Figure(dpi = 50)
    ax = fig.add_subplot()

    #create canvas for fft plot
    canvas = FigureCanvasTkAgg(fig, master=app)
    plot_obj = canvas.get_tk_widget()
    canvas.draw()
    plot_obj.grid(row=10, column = 0,  pady=PADY, padx = PADX)

    #create new figure for mapping plot
    # create a 10x10 grid of zeros
    map_data = np.zeros((10,10))

    # create the figure
    map_fig = Figure(dpi = 50)
    map_ax = map_fig.add_subplot()

    cmap = colors.ListedColormap(['gray', 'green'])
    bounds = [0,1,2]
    norm = colors.BoundaryNorm(bounds, cmap.N)

    map_ax.imshow(map_data, cmap=cmap, norm=norm)

    map_ax.grid(which='major', axis='both', linestyle='-', color='k', linewidth=2)
    map_ax.set_xticks(np.arange(-.5, 10, 1))
    map_ax.set_yticks(np.arange(-.5, 10, 1))

    map_canvas = FigureCanvasTkAgg(map_fig, master=app)
    map_plot_obj = map_canvas.get_tk_widget()
    map_canvas.draw()
    map_plot_obj.grid(row=10, column = 2, pady=PADY, padx = PADX)

    #schedule an event to update the plot
    def update():
        try:
            #update the matplotlib plot in the app
            if not fft_plot_queue.empty():
                # print("updating plot")
                fft_data, frequency_bins = fft_plot_queue.get()
                #erase fig
                ax.clear()
                # draw on new data
                
                ax.plot(frequency_bins, np.abs(fft_data))

                canvas.draw()

            if not bool_audio_pos_queue.empty():
                #update the mapping plot
                map_ax.clear()
                #redraw lines
                map_ax.grid(which='major', axis='both', linestyle='-', color='k', linewidth=2)
                map_ax.set_xticks(np.arange(-.5, 10, 1))
                map_ax.set_yticks(np.arange(-.5, 10, 1))
                
                result, data, pos = bool_audio_pos_queue.get()

                map_data[pos[0], pos[1]] = 1 if result else 2

                map_ax.imshow(map_data, cmap=cmap, norm=norm)
                map_canvas.draw()


            app.after(100, update)
        except:
            raise Exception("Error updating plot")

    app.after(1, update)
    app.mainloop()

    # kill all processes if they exist
    for process in processes:
        try:
            process.terminate()
        except AttributeError:
            pass

