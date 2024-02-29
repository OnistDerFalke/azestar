#ifndef AZESTAR_STRUCTURE_H
#define AZESTAR_STRUCTURE_H


class structure {
public:
    virtual void run_base() = 0;

private:
    virtual void show_settings_window() = 0;
    virtual void show_simulation_window() = 0;
};


#endif
