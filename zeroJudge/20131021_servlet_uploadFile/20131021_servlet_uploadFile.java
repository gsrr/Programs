public void doPost(HttpServletRequest request, HttpServletResponse response)
	throws ServletException, IOException {
		try
		{
			List<FileItem> items = new ServletFileUpload(new DiskFileItemFactory()).parseRequest(request);
			for (FileItem item : items) 
			{
				logger.error(item.getFieldName() + ",");
				if (item.isFormField()) 
				{
					// Process regular form field (input type="text|radio|checkbox|etc", select, etc).
					String fieldname = item.getFieldName();
					String fieldvalue = item.getString();
					// ... (do your job here)
				} 
				else 
				{
					// Process form file field (input type="file").
					String fieldname = item.getFieldName();
					String filename = FilenameUtils.getName(item.getName());
					InputStream filecontent = item.getInputStream();
					// ... (do your job here)
					BufferedOutputStream outStream = new BufferedOutputStream(new FileOutputStream("/tmp/tempUpload"));
					byte[] contentBuffer = new byte[8192];
					int length;
					while((length = filecontent.read(contentBuffer)) != -1)
					{
						outStream.write(contentBuffer, 0, length);
					}
					outStream.close();
				}
			}
		}
		catch(FileUploadException e)
		{
			throw new ServletException("Can not parse multipart request");
		}


	}
