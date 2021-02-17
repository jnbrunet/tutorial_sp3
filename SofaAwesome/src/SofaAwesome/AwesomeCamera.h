#pragma once
#include <SofaBaseVisual/BaseCamera.h>

class AwesomeCamera : public sofa::component::visualmodel::BaseCamera {
    using Base = sofa::component::visualmodel::BaseCamera;
    template <typename T> using Data = sofa::core::objectmodel::Data<T>;

public:
    SOFA_CLASS(AwesomeCamera, sofa::component::visualmodel::BaseCamera);

    /**
     * Main constructor of the camera
     */
    AwesomeCamera();

    /**
     * Render the current frame from the point of view of the camera into an image and return it.
     */
    const char * grab_frame();

    /**
     * Render the current frame and save it into a file.
     *
     * @param filepath Path to the file where the frame will be saved.
     */
    void save_frame(const std::string & filepath);

    /**
     * Replace %s and %i in filepath for the component name and step number, respectively.
     */
    virtual std::string parse_file_path(std::string filepath) const;

private:
    void reset() final { p_step_number = 0; }
    void handleEvent(sofa::core::objectmodel::Event*) final;
    void manageEvent(sofa::core::objectmodel::Event*) final {}

    // Data members
    Data<std::string> d_filepath;
    Data<bool> d_save_frame_before_first_step;
    Data<unsigned int> d_save_frame_after_each_n_steps;

    // Private members
    unsigned int p_step_number = 0;
};
