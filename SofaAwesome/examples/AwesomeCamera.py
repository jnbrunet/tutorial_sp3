import Sofa
from SofaAwesome import AwesomeCamera
from datetime import datetime

class AnotherAwesomeCamera(AwesomeCamera):
    def parse_file_path(self, filepath):
        parsed_filepath = AwesomeCamera.parse_file_path(self, filepath)
        date = datetime.now().strftime("%d_%m_%y_%H_%M_%S")
        return parsed_filepath.replace("%d", date)

root = Sofa.Core.Node()
camera_1 = root.addObject(AwesomeCamera())
camera_1.save_frame("screenshot_%s_%i_%d.jpg")

camera_2 = root.addObject(AnotherAwesomeCamera())
camera_2.save_frame("screenshot_%s_%i_%d.jpg")