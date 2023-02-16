/*
 * Copyright 2009,2011, Haiku, Inc.
 * Distributed under the terms of the MIT License.
 */
#ifndef _PACKAGE__HPKG__PACKAGE_WRITER_H_
#define _PACKAGE__HPKG__PACKAGE_WRITER_H_


#include <SupportDefs.h>

#include <package/hpkg/ErrorOutput.h>


class BPositionIO;


namespace BPackageKit {

namespace BHPKG {

namespace BPrivate {
	class PackageWriterImpl;
}
using BPrivate::PackageWriterImpl;


class BPackageWriterListener : public BErrorOutput {
public:
	virtual	void				PrintErrorVarArgs(const char* format,
									va_list args) = 0;

	virtual	void				OnEntryAdded(const char* path) = 0;

	virtual void				OnTOCSizeInfo(uint64 uncompressedStringsSize,
									uint64 uncompressedMainSize,
									uint64 uncompressedTOCSize) = 0;
	virtual void				OnPackageAttributesSizeInfo(uint32 stringCount,
									uint32 uncompressedSize) = 0;
	virtual void				OnPackageSizeInfo(uint32 headerSize,
									uint64 heapSize, uint64 tocSize,
									uint32 packageAttributesSize,
									uint64 totalSize) = 0;
};


class BPackageWriterParameters {
public:
								BPackageWriterParameters();
								~BPackageWriterParameters();

			uint32				Flags() const;
			void				SetFlags(uint32 flags);

			uint32				Compression() const;
			void				SetCompression(uint32 compression);

			int32				CompressionLevel() const;
			void				SetCompressionLevel(int32 compressionLevel);

private:
			uint32				fFlags;
			uint32				fCompression;
			int32				fCompressionLevel;
};


class BPackageWriter {
public:
								BPackageWriter(
									BPackageWriterListener* listener);
								~BPackageWriter();

			status_t			Init(const char* fileName,
									const BPackageWriterParameters* parameters
										= NULL);
			status_t			Init(BPositionIO* file, bool keepFile,
									const BPackageWriterParameters* parameters
										= NULL);
			status_t			SetInstallPath(const char* installPath);
			void				SetCheckLicenses(bool checkLicenses);
			status_t			AddEntry(const char* fileName, int fd = -1);
			status_t			Finish();

			status_t			Recompress(BPositionIO* inputFile);
									// to be called after Init(); no Finish()

private:
			PackageWriterImpl*	fImpl;
};


}	// namespace BHPKG

}	// namespace BPackageKit


#endif	// _PACKAGE__HPKG__PACKAGE_WRITER_H_
