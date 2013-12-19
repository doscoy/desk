/* -------------------------------------------------------------------------------
	�Q�ƃJ�E���g�v�����N���X
---------------------------------------------------------------------------------*/

#ifndef HPP_REF_COUNTABLE_INCLUDED
#define HPP_REF_COUNTABLE_INCLUDED



namespace nd {


// =================================================================
//	�Q�ƃJ�E���g�𒍓�����N���X
class RefCountable
{
// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
protected:
	// *************************************************************************
	//	�f�t�H���g�R���X�g���N�^
	RefCountable()
		: ref_count_( 0 )
		{
	}
	
	// *************************************************************************
	//	�f�X�g���N�^
    virtual ~RefCountable()
    {
    }


// -----------------------------------------------------------------
//	�R�s�[�֎~
private:
	// *************************************************************************
	//	�R�s�[�R���X�g���N�^
	RefCountable( const RefCountable& );
	
	// *************************************************************************
	//	������Z�q�I�y���[�^
	RefCountable& operator =( const RefCountable& );


// -----------------------------------------------------------------
//	���J���\�b�h
public:
	// *************************************************************************
	//	�Q�ƃJ�E���g���Z
	void addReference()
	{
		ref_count_ += 1;
	}
	
	// *************************************************************************
	//	�Q�ƃJ�E���g���Z
	void releaseReference()
	{
		ref_count_ -= 1;
		
		if ( ref_count_ == 0 ){
			withoutReference();
		}
	}
	
	// *************************************************************************
	//	�Q�Ƃ������Ȃ������̏���
	virtual void withoutReference()
	{
		delete this;
	}


// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	int ref_count_;

};

} // namespace nd

#endif // HPP_REF_COUNTABLE_INCLUDED