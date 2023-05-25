#pragma once

#include "Model.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class Object3d
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �萔
	// �{�[���̍ő吔
	static const int MAX_BONES = 32;

public: // �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����(���W�ϊ��s��p)
	struct ConstBufferDataTransform {
		XMMATRIX viewProj;		// �r���[�v���W�F�N�V�����s��
		XMMATRIX world;			// ���[���h�s��
		XMFLOAT3 cameraPos;	// �J�������W(���[���h���W)
	};

	// �萔�o�b�t�@�p�f�[�^�\����(�X�L�j���O)
	struct ConstBufferDataSkin {
		XMMATRIX bones[MAX_BONES];
	};

public: // �ÓI�����o�֐�
	// setter
	static void SetDevice(ID3D12Device* device) { Object3d::device = device; }
	static void SetCamera(Camera* camera) { Object3d::camera = camera; }

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C���̐���
	/// </summary>
	static void CreateGraphicsPipeline();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �J����
	static Camera* camera;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;

public: // �����o�ϐ�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// ���f���̃Z�b�g
	/// </summary>
	/// <param name="model">���f��</param>
	void SetModel(Model* model) { this->model = model; }

	/// <summary>
	/// �A�j���[�V�����J�n
	/// </summary>
	void PlayAnimation();

protected: // �����o�ϐ�
	// �萔�o�b�t�@(���W�ϊ��s��)
	ComPtr<ID3D12Resource> constBuffTransform;
	// �萔�o�b�t�@(�X�L��)
	ComPtr<ID3D12Resource> constBuffSkin;
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1, 1, 1 };
	// X, Y, Z������̃��[�J����]�p
	XMFLOAT3 rotation = { 0, 0, 0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0, 0, 0 };
	// ���[�J�����[���h���W�s��
	XMMATRIX matWorld;
	// ���f��
	Model* model = nullptr;

	// 1�t���[���̎���
	FbxTime frameTime;
	// �A�j���[�V�����J�n����
	FbxTime startTime;
	// �A�j���[�V�����I������
	FbxTime endTime;
	// ���ݎ��ԁi�A�j���[�V�����j
	FbxTime currentTime;
	// �A�j���[�V�����Đ���
	bool isPlay = false;
};
