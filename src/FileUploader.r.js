import React from "react";
import axios from "axios";
import { useDropzone } from "react-dropzone";

const FileUploader = ({ endpoint, resourceName, resourceId }) => {
  const onDrop = React.useCallback(files => {
    let formData = new FormData();
    formData.append("file", files[0]);
    formData.append(`${resourceName}_id`, resourceId);
    axios
      .post(endpoint, formData)
      .then(res => console.log(res))
      .catch(err => console.error(err));
  }, []);
  const { getRootProps, getInputProps, isDragActive } = useDropzone({ onDrop });

  return (
    <div {...getRootProps()}>
      <input {...getInputProps()} />
      {isDragActive ? (
        <p>Drop the files here ...</p>
      ) : (
        <p>Drag 'n' drop some files here, or click to select files</p>
      )}
    </div>
  );
};

export default FileUploader;
