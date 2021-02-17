#include "AwesomeCamera.h"

#include <sofa/core/ObjectFactory.h>
#include <sofa/simulation/events/SimulationInitTexturesDoneEvent.h>
#include <sofa/simulation/AnimateEndEvent.h>

AwesomeCamera::AwesomeCamera()
:  d_filepath(initData(&d_filepath,
    std::string("screenshot_%s_%i.jpg"),
    "filepath",
    "Path of the image file. The special character set '%s' and '%i' can be used in the file name to specify the camera "
    "name and the step number, respectively. Note that the step number will be 0 before the first step of the simulation, "
    "and i after the ith step has been simulated.",
    true  /*is_displayed_in_gui*/,
    false /*is_read_only*/ ))
, d_save_frame_before_first_step(initData(&d_save_frame_before_first_step,
    false,
    "save_frame_before_first_step",
    "Render the frame once the scene has been initialized completely (before even starting the first step) "
    "and save it into 'filepath'. Default to false",
    true  /*is_displayed_in_gui*/,
    false /*is_read_only*/ ))
, d_save_frame_after_each_n_steps(initData(&d_save_frame_after_each_n_steps,
    static_cast<unsigned int> (0),
    "save_frame_after_each_n_steps",
    "Render the frame after every N steps and save it into 'filepath'. Set to zero to disable."
    "Default to 0",
    true  /*is_displayed_in_gui*/,
    false /*is_read_only*/ ))
{
    this->f_printLog.setValue(true); // This is just for the demonstration, don't do this in your code
}

const char *AwesomeCamera::grab_frame() {
    msg_info() << "Grabbing the frame";
    return nullptr;
}

void AwesomeCamera::save_frame(const std::string &filepath) {
    const std::string parsed_file_path = parse_file_path(filepath);
    msg_info() << "Saving the frame to " << parsed_file_path;
}

std::string AwesomeCamera::parse_file_path (std::string filepath) const {
    std::vector<std::pair<std::string, std::string>> keys = {
            {"%s", this->getName()},
            {"%i", std::to_string(p_step_number)}
    };
    for (const auto & k : keys) {
        size_t start_pos = 0;
        while((start_pos = filepath.find(k.first, start_pos)) != std::string::npos) {
            filepath.replace(start_pos, k.first.length(), k.second);
            start_pos += k.second.length();
        }
    }

    return filepath;
}

void AwesomeCamera::handleEvent(sofa::core::objectmodel::Event * ev) {
    using SimulationInitTexturesDoneEvent= sofa::simulation::SimulationInitTexturesDoneEvent;
    using AnimateEndEvent= sofa::simulation::AnimateEndEvent;

    BaseCamera::handleEvent( ev );

    const auto & save_frame_before_first_step = d_save_frame_before_first_step.getValue();
    const auto & save_frame_after_each_n_steps = d_save_frame_after_each_n_steps.getValue();

    if (SimulationInitTexturesDoneEvent::checkEventType(ev) && d_save_frame_before_first_step.getValue()) {
        const auto & filepath = parse_file_path(d_filepath.getValue());
        save_frame(filepath);
    } else if (AnimateEndEvent::checkEventType(ev)) {
        ++p_step_number;

        if (save_frame_after_each_n_steps > 0 && (p_step_number % save_frame_after_each_n_steps) == 0) {
            const auto & filepath = parse_file_path(d_filepath.getValue());
            save_frame(filepath);
        }
    }
}

int AwesomeCameraClass = sofa::core::RegisterObject("Awesome rendering camera.")
        .add< AwesomeCamera >()
;
