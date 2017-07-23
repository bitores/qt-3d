#ifndef _Encrypt_H__
#define _Encrypt_H__

#include "utils/include/IteratorWrappers.h"
#include "utils/include/StringVector.h"
#include "io/DataStream.h"

class Encrypt
{
public:
	virtual ~Encrypt();

	virtual MemoryDataStreamPtr Decrypt(DataStreamPtr& input)= 0;

	/** Returns the type of the encrypt as a String
	*/
	virtual String getType() const = 0;

};

class EncryptManager
{
private:
	typedef map< String, Encrypt* > EncryptList;
	/** A map that contains all the registered encrypt.
	*/
	EncryptList msMapEncrypts;

	typedef ConstMapIterator<EncryptList> EncryptIterator;

public:
	~EncryptManager();

	/** Registers a new encrypt in the database.
	*/
	void registerEncrypt( Encrypt *pEncrypt);

	/** Return whether a encrypt is registered already.
	*/
	bool isEncryptRegistered( const String& encryptType );

	/** Unregisters a encrypt from the database.
	*/
	void unregisterEncrypt( Encrypt *pEncrypt );

	/** Gets the iterator for the registered encrypts. */
	EncryptIterator getEncryptIterator(void) {
		return EncryptIterator(msMapEncrypts.begin(), msMapEncrypts.end());
	}
	/** Gets the file extension list for the registered encrypts. */
	StringVector getExtensions(void);

	/** Gets the encrypt registered for the passed in file extension. */
	Encrypt* getEncrypt(const String& extension);
};
/** @} */
/** @} */

#endif
