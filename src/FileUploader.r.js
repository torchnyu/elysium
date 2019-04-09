import React from "react";
import {useDropzone} from 'react-dropzone'

const FileUploader = ({ handleFiles }) => {
  const onDrop = React.useCallback(handleFiles, []);
  const {getRootProps, getInputProps, isDragActive} = useDropzone({onDrop})

  return (
    <div {...getRootProps()}>
      <input {...getInputProps()} />
      {
        isDragActive ?
          <p>Drop the files here ...</p> :
          <p>Drag 'n' drop some files here, or click to select files</p>
      }
    </div>
  )
}

export default FileUploader;
